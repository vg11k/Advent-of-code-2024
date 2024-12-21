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


struct Position {
    int x;
    int y;
    Position() : x(-1), y(-1) {}
    Position(int a, int b) : x(a), y(b) {}
};

inline bool operator<(const Position& lhs, const Position& rhs)
{
    if(lhs.x != rhs.x) return lhs.x < rhs.x;
    return lhs.y < rhs.y;
}

string getCharAt(vector<string> s, int x, int y) {
    return s.at(y).substr(x, 1);
}

void loopDoStuff(vector<string> input) {
    for (string sinput : input) {
        istringstream iss(sinput);
        string s;
        while (getline(iss, s, ' ')) {
            int val = stoi(s);

        }
    }
}

long long part1(vector<string> allLines, map<string, vector<Position*>*> characToCoords) {

    long long cptAntinodes = 0;

    set<Position> antinodesCoordinates;

    for (auto iter = characToCoords.begin(); iter != characToCoords.end(); ++iter)
    {
        vector<Position*> * positionsInput = iter->second;
        for (int i = 0; i < positionsInput->size(); i++) {
            for (int j = 0; j < positionsInput->size(); j++) {
                if (i != j) {

                    Position * p1 = positionsInput->at(i);
                    Position * p2 = positionsInput->at(j);

                    int x = 2 *(p1->x) - p2->x;
                    int y = 2 * (p1->y) - p2->y;

                    if (x > -1 && x < allLines.at(0).size() &&
                        y > -1 && y < allLines.size()) {

                        Position res1(x, y);
                        antinodesCoordinates.insert(res1);
                        allLines.at(res1.y).replace(res1.x, 1, "#");
                    }

                    x = 2 * (p2->x) - p1->x;
                    y = 2 * (p2->y) - p1->y;


                    if (x > -1 && x < allLines.at(0).size() &&
                        y > -1 && y < allLines.size()) {


                        Position res2(x, y);
                        antinodesCoordinates.insert(res2);
                        allLines.at(res2.y).replace(res2.x, 1, "#");
                    }
                }
            }
        }
    }

    cout << "visu" << endl;

    for (int i = 0; i < allLines.size(); i++) {
        cout << allLines.at(i) << endl;
    }

    return antinodesCoordinates.size();
}

long long part2(vector<string> allLines, map<string, vector<Position*>*> characToCoords) {

    long long cptAntinodes = 0;

    set<Position> antinodesCoordinates;

    for (auto iter = characToCoords.begin(); iter != characToCoords.end(); ++iter)
    {
        vector<Position*>* positionsInput = iter->second;
        for (int i = 0; i < positionsInput->size(); i++) {
            for (int j = 0; j < positionsInput->size(); j++) {
                if (i != j) {

                    Position* p1 = positionsInput->at(i);
                    Position* p2 = positionsInput->at(j);

                    int x = 2 * (p1->x) - p2->x;
                    int y = 2 * (p1->y) - p2->y;

                    Position res1(x, y);

                    if (x > -1 && x < allLines.at(0).size() &&
                        y > -1 && y < allLines.size()) {

                        antinodesCoordinates.insert(res1);
                        allLines.at(res1.y).replace(res1.x, 1, "#");
                    }



                    Position tmp(p1->x, p1->y);
                    for (int k = 0; k < 60; k++) {

                        x = 2 * (res1.x) - tmp.x;
                        y = 2 * (res1.y) - tmp.y;

                       
                        tmp.x = res1.x;
                        tmp.y = res1.y;

                        res1.x = x;
                        res1.y = y;

                        if (x > -1 && x < allLines.at(0).size() &&
                            y > -1 && y < allLines.size()) {

                            antinodesCoordinates.insert(res1);
                            allLines.at(res1.y).replace(res1.x, 1, "#");
                        }
                    }


                    x = 2 * (p2->x) - p1->x;
                    y = 2 * (p2->y) - p1->y;

                    Position res2(x, y);

                    if (x > -1 && x < allLines.at(0).size() &&
                        y > -1 && y < allLines.size()) {

                        antinodesCoordinates.insert(res2);
                        allLines.at(res2.y).replace(res2.x, 1, "#");
                    }

                    tmp.x = p2->x;
                    tmp.y = p2->y;

                    for (int k = 0; k < 60; k++) {

                        x = 2 * (res2.x) - tmp.x;
                        y = 2 * (res2.y) - tmp.y;


                        tmp.x = res2.x;
                        tmp.y = res2.y;

                        res2.x = x;
                        res2.y = y;

                        if (x > -1 && x < allLines.at(0).size() &&
                            y > -1 && y < allLines.size()) {

                            antinodesCoordinates.insert(res2);
                            allLines.at(res2.y).replace(res2.x, 1, "#");
                        }
                    }
                    

                    Position p3(p1->x, p1->y);
                    Position p4(p2->x, p2->y);

                    antinodesCoordinates.insert(p3);
                    antinodesCoordinates.insert(p4);

                }
            }
        }
    }

    cout << "visu" << endl;

    for (int i = 0; i < allLines.size(); i++) {
        cout << allLines.at(i) << endl;
    }

    return antinodesCoordinates.size();
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

    while (getline(infile, line)) {
        allLines.push_back(line);
    }

    map<string,vector<Position*>*> characToCoords;
    for (int y = 0; y < allLines.size(); y++) {
        for(int x = 0; x < allLines.at(0).size(); x++) {
            string s = getCharAt(allLines, x, y);
            if (characToCoords[s] == NULL) characToCoords[s] = new vector<Position*>();
            if (s != ".") {
                Position * p = new Position(x, y);
                characToCoords[s]->push_back(p);
            }
        }
    }

    result1 = part1(allLines, characToCoords);
    result2 = part2(allLines, characToCoords);


    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}