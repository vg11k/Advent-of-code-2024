#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <set>

using namespace std;

static const string filename = "input.txt";
//static const string filename = "example.txt";

static const int ITERMAX = 10000000000;

struct Position {
	int x;
	int y;
	Position() : x(-1), y(-1) {}
	Position(int a, int b) : x(a), y(b) {}
};


enum State { TOP, BOT, LEFT, RIGHT };

struct HistoPos {
	Position pos;
	State direction;
	long long loopIt;
	HistoPos() { cout << "ERROR NE DEVRAIT PAS PASSER LA" << endl; }
	HistoPos(Position p, State s, long long i) : pos(p), direction(s), loopIt(i) {}
	bool isSameAndInPast(Position p, State s, long long i) {
		if (p.x == pos.x && p.y == pos.y && s == direction && i < loopIt) return true;
		return false;
	}
};


string getCharAt(vector<string> s, int x, int y) {
	return s.at(y).substr(x, 1);
}

Position findstart(vector<string> input) {
	for (int linecpt = 0; linecpt < input.size(); linecpt++) {
		string sinput = input.at(linecpt);
		if (sinput.find('^') != std::string::npos) {
			return Position(sinput.find('^'), linecpt);
		}
	}
	cout << "failed to find start" << endl;
	return Position(0, 0);
}

void showVisu(vector<string> input, Position position, State direction) {
	for (int linecpt = 0; linecpt < input.size(); linecpt++) {
		string s = input.at(linecpt);
		if (linecpt == position.y) {
			string dir;
			switch (direction) {
			case TOP: dir = "^"; break;
			case BOT: dir = "v"; break;
			case RIGHT: dir = ">"; break;
			case LEFT: dir = "<"; break;
			default: cout << "TOTO" << endl;
			}

			s.replace(position.x, 1, dir);

		}
		cout << s << endl;
	}
	cout << "=========================================" << endl;
}

bool seekThisOtherPosition(vector<string> allLines,
	Position positionCaillou,
	long long itermax,
	Position startPos)
{
	long long cptLoop = 0;
	int mapWidth = allLines.at(0).size();
	int mapHeight = allLines.size();
	allLines.at(positionCaillou.y).replace(positionCaillou.x, 1, "O");

	vector<HistoPos> positionsHisto;

	map<State, vector<HistoPos>> positionByDirection = map<State, vector<HistoPos>>();

	Position pos = startPos;
	State direction = TOP;

	while (pos.x > -1 && pos.x < mapWidth && pos.y > -1 && pos.y < mapHeight && cptLoop < itermax)
	{
		switch (direction) {
			case TOP: {
				if (pos.y > 0) {
					string topPos = getCharAt(allLines, pos.x, pos.y - 1);
					if (topPos == ".") {
						positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
						positionByDirection[direction].push_back(HistoPos(pos, direction, cptLoop));
						pos.y--;
					}
					else {
						direction = RIGHT;
					}
				}
				else pos.y--;
			}
			break;
			case BOT: {
				if (pos.y < mapHeight - 1) {
					string botPos = getCharAt(allLines, pos.x, pos.y + 1);
					if (botPos == ".") {
						positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
						positionByDirection[direction].push_back(HistoPos(pos, direction, cptLoop));
						pos.y++;
					}
					else {
						direction = LEFT;
					}
				}
				else pos.y++;
			}
			break;
			case RIGHT: {
				if (pos.x < mapWidth - 1) {
					string rigPos = getCharAt(allLines, pos.x + 1, pos.y);
					if (rigPos == ".") {
						positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
						positionByDirection[direction].push_back(HistoPos(pos, direction, cptLoop));
						pos.x++;
					}
					else { 
						direction = BOT; 
					}
				}
				else pos.x++;
			}
			break;
			case LEFT: {

				if (pos.x > 0) {
					string lefPos = getCharAt(allLines, pos.x - 1, pos.y);
					if (lefPos == ".") {
						positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
						positionByDirection[direction].push_back(HistoPos(pos, direction, cptLoop));
						pos.x--;
					}
					else {
						direction = TOP; 
					}
				}
				else pos.x--;
			}
			break;
			default:
				cout << "BOUUUUUUH" << endl;
		}


		for (int i = 0; i < positionByDirection[direction].size(); i++) {
			HistoPos histoPosPast = positionByDirection[direction].at(i);
			if (histoPosPast.isSameAndInPast(pos, direction, i)) {
				return true;
			}
		}
		cptLoop++;
	}

	return false;
}

struct PartOneResult {
	long long result;
	vector<HistoPos> positionsHisto;
};

PartOneResult partOne(vector<string> allLines) {

	Position startPos = findstart(allLines);
	allLines.at(startPos.y).replace(startPos.x, 1, ".");
	string sstartPos = to_string(startPos.x) + "-" + to_string(startPos.y);

	PartOneResult result;

	int mapWidth = allLines.at(0).size();
	int mapHeight = allLines.size();

	set<string> visitedCoordinates;
	set<string> visitedCoordinateswstates;

	map<State, vector<string>> stateToVisitedCoordinates;
	Position pos = Position(startPos.x, startPos.y);

	visitedCoordinates.insert(to_string(pos.x) + "-" + to_string(pos.y));

	State direction = TOP;
	vector<HistoPos> positionsHisto;


	long long cptLoop = 0;
	while (pos.x > -1 && pos.x < mapWidth && pos.y > -1 && pos.y < mapHeight) {
		string templatePos = to_string(pos.x) + "-" + to_string(pos.y);
		visitedCoordinates.insert(templatePos);
		//showVisu(allLines, pos, direction);  
		switch (direction) {
		case TOP:
		{
			if (pos.y > 0) {
				string topPos = getCharAt(allLines, pos.x, pos.y - 1);
				if (topPos == ".") {
					positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
					pos.y--;
				}
				else {
					direction = RIGHT;
				}
			}
			else pos.y--;
		}
		break;
		case BOT:
		{
			if (pos.y < mapHeight - 1) {
				string botPos = getCharAt(allLines, pos.x, pos.y + 1);
				if (botPos == ".") {
					positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
					pos.y++;
				}
				else {
					direction = LEFT;
				}
			}
			else pos.y++;
		}
		break;
		case RIGHT:
		{
			if (pos.x < mapWidth - 1) {
				string rigPos = getCharAt(allLines, pos.x + 1, pos.y);
				if (rigPos == ".") {
					positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
					pos.x++;
				}
				else {
					direction = BOT;
				}
			}
			else pos.x++;
		}
		break;
		case LEFT:
		{
			if (pos.x > 0) {
				string lefPos = getCharAt(allLines, pos.x - 1, pos.y);
				if (lefPos == ".") {
					positionsHisto.push_back(HistoPos(pos, direction, cptLoop));
					pos.x--;
				}
				else {
					direction = TOP;
				}
			}
			else pos.x--;
		}
		break;
		default:
			cout << "BOUUUUUUH" << endl;
		}

		cptLoop++;
	}

	result.positionsHisto = positionsHisto;
	result.result = visitedCoordinates.size();
	return result;
}

int partTwo(vector<string> allLines, PartOneResult p1) {

	long long result = 0;

	Position startPos = findstart(allLines);
	allLines.at(startPos.y).replace(startPos.x, 1, ".");

	vector<HistoPos> positionsHisto = p1.positionsHisto;

	int mapWidth = allLines.at(0).size();
	int mapHeight = allLines.size();

	vector<Position> solutions;
	long long ccpt = 0;
	//std::reverse(positionsHisto.begin(), positionsHisto.end());
	long long maxiterToUse = ITERMAX;


	vector<HistoPos> positionToHandle;
	for (HistoPos histoPos : positionsHisto) {
		HistoPos hp(Position(histoPos.pos.x, histoPos.pos.y), histoPos.direction, histoPos.loopIt);
		positionToHandle.push_back(hp);
	}


	vector<HistoPos> positionsHisto4nextIteration;
	vector<Position> positionCailloux;

	for (HistoPos histoPos : positionToHandle)
	{

		Position positionCaillou;

		switch (histoPos.direction)
		{
		case TOP:
		{
			positionCaillou = Position(histoPos.pos.x, histoPos.pos.y - 1);
		}
		break;
		case BOT:
		{
			positionCaillou = Position(histoPos.pos.x, histoPos.pos.y + 1);
		}
		break;
		case RIGHT:
		{
			positionCaillou = Position(histoPos.pos.x + 1, histoPos.pos.y);
		}
		break;
		case LEFT:
		{
			positionCaillou = Position(histoPos.pos.x - 1, histoPos.pos.y);
		}
		break;
		default: cout << "wtf" << endl;
		}

		bool keepCaillou = true;
		for (int i = 0; i < positionCailloux.size() && keepCaillou; i++) {
			if (positionCailloux.at(i).x == positionCaillou.x && positionCailloux.at(i).y == positionCaillou.y) {
				keepCaillou = false;
			}
		}

		if (keepCaillou) {
			positionCailloux.push_back(positionCaillou);
		}
	}

	for(Position positionCaillou : positionCailloux) {

		bool response = seekThisOtherPosition(allLines, positionCaillou, maxiterToUse, startPos);
				
		if (response) {
			result++;
			solutions.push_back(positionCaillou);
		}

		ccpt++;
		cout << result << " " << ccpt << "/" << positionCailloux.size() << endl;
	}
	return result;
}

int main(char* args[]) {


	cout << "Hello World !" << endl;
	bool debug = false;

	clock_t start, end;

	ifstream infile(filename.c_str());
	string line;
	long long result1 = 0;
	long long result2 = 0;
	vector<string> allLines;
	start = clock();
	while (getline(infile, line))
	{
		allLines.push_back(line);
	}

	PartOneResult p1 = partOne(allLines);
	result1 = p1.result;
	result2 = partTwo(allLines, p1);

	end = clock();
	cout << "result1 : " << result1 << endl;
	cout << "result2 : " << result2 << endl; //2262
	cout << end - start << " ms to compute." << endl;
	cout << "Bye World !" << endl;
	return 0;
}
