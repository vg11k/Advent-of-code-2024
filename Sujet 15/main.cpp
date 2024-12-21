#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

static const string filename = "input.txt";
//static const string filename = "example1.txt";
//static const string filename = "example2.txt";
//static const string filename = "example3.txt";

static const bool verbose = false;

string getCharAt(vector<string> s, int x, int y) {
    return s.at(y).substr(x, 1);
}

enum Content {WALL, FISH, BOX, NOTHING, BOXL, BOXR};
enum Move {RIGHT, LEFT, TOP, BOT};

void visu(vector<vector<Content>> inputMap) {
    for(int i = 0; i <inputMap.size(); i++) {
        for(int j = 0; j < inputMap.at(0).size(); j++) {
            switch(inputMap.at(i).at(j)) {
                case (WALL): cout << "#"; break;
                case (FISH) : cout << "@"; break;
                case (BOX) : cout << "O"; break;
                case (NOTHING) : cout << "."; break;
                case (BOXR) : cout << "]"; break;
                case (BOXL) : cout << "["; break;
                //defaut cout << "wtf";
            }
        }
        cout << endl;
    }

    cout << endl << endl << " ================================== " << endl << endl;

}

struct Box {
    int leftx; 
    int lefty;
    int rightx;
    int righty;
    Box() {        leftx = -1; lefty = -1; rightx = -1; righty = -1;    }
    Box(int a, int b, int c, int d) : leftx(a), lefty(b), rightx(c), righty(d) {}
    Box(const Box &b) {
        leftx = b.leftx; 
        lefty = b.lefty;
        rightx = b.rightx;
        righty = b.righty;
    }
};

vector<Box> recurGetBoxesToMove(vector<vector<Content>> & inputMap, Box rootBox, Move direction) {
    
    vector<Box> result;
    Box self(rootBox);

    int movey = 1;
    if(direction == TOP) movey = -1;

    Content upRight = inputMap.at(rootBox.righty + movey).at(rootBox.rightx);
    Content upLeft = inputMap.at(rootBox.lefty + movey).at(rootBox.leftx);

    if(upRight == NOTHING && upLeft == NOTHING) {
        result.push_back(self);
    }
    else if(upRight == WALL || upLeft == WALL) {
        return result;
    }
    else {
        if(upRight == BOXR) {
            Box topBox(self);
            topBox.lefty += movey;
            topBox.righty += movey;
            vector<Box> childBox = recurGetBoxesToMove(inputMap, topBox, direction);
            if(!childBox.empty()) {
                for(Box b : childBox) result.push_back(b);
                result.push_back(self);
            }
        }
        else {
            bool greenForRight = true;
            bool greenForLeft = true;

            if(upRight == BOXL) {
                Box topBox(self);
                topBox.lefty += movey;
                topBox.righty += movey;
                topBox.rightx +=1;
                topBox.leftx +=1;
                vector<Box> childBox = recurGetBoxesToMove(inputMap, topBox, direction);
                if(!childBox.empty()) {
                    for(Box b : childBox) result.push_back(b);
                }
                else {
                    greenForRight = false;
                }
            }
            if(upLeft == BOXR) {
                Box topBox(self);
                topBox.lefty += movey;
                topBox.righty += movey;
                topBox.rightx -=1;
                topBox.leftx -=1;
                vector<Box> childBox = recurGetBoxesToMove(inputMap, topBox, direction);
                if(!childBox.empty()) {
                    for(Box b : childBox) result.push_back(b);
                }
                else {
                    greenForLeft = false;
                }
            }

            if(!greenForLeft || !greenForRight) result = vector<Box>();
            else result.push_back(self);
        }
    }
    
    return result;
}

void loopDoStuff(vector<string> input, 
    vector<vector<Content>> & inputMap, 
    vector<Move> &inputMoves) {

    bool part2 = false;
    for (string sinput : input) {
        if(sinput.empty()) {
            part2 = true;
        }
        else {
            if(!part2) {
                inputMap.push_back(vector<Content>());
            }

            for(int i = 0; i < sinput.size(); i++) {
                string ss = sinput.substr(i, 1);
                if(!part2) {
                    if(ss == "#") inputMap.at(inputMap.size() - 1).push_back(WALL);
                    else if(ss == "@") inputMap.at(inputMap.size() - 1).push_back(FISH);
                    else if(ss == "O") inputMap.at(inputMap.size() - 1).push_back(BOX);
                    else if(ss == ".") inputMap.at(inputMap.size() - 1).push_back(NOTHING);
                    else cout<<sinput<< endl;
                }
                else {
                    if(ss == "<") inputMoves.push_back(LEFT);
                    else if(ss == ">") inputMoves.push_back(RIGHT);
                    else if(ss == "v") inputMoves.push_back(BOT);
                    else inputMoves.push_back(TOP);
                }
            }
        }
    }

    cout << "out building" <<endl;
}

void loopDoStuff2(vector<string> input, 
    vector<vector<Content>> & inputMap) {

    bool part2 = false;
    for (string sinput : input) {
        if(sinput.empty()) {
            part2 = true;
        }
        else {
            if(!part2) {
                inputMap.push_back(vector<Content>());
            }

            for(int i = 0; i < sinput.size() && !part2; i++) {
                string ss = sinput.substr(i, 1);
                if(!part2) {
                    if(ss == "#") {
                        inputMap.at(inputMap.size() - 1).push_back(WALL);
                        inputMap.at(inputMap.size() - 1).push_back(WALL);
                    } 
                    else if(ss == "@") {
                        inputMap.at(inputMap.size() - 1).push_back(FISH);
                        inputMap.at(inputMap.size() - 1).push_back(NOTHING);
                    }
                    else if(ss == "O") {
                        inputMap.at(inputMap.size() - 1).push_back(BOXL);
                        inputMap.at(inputMap.size() - 1).push_back(BOXR);
                    }
                    else if(ss == ".") {
                        inputMap.at(inputMap.size() - 1).push_back(NOTHING);
                        inputMap.at(inputMap.size() - 1).push_back(NOTHING);
                    }
                    else cout<<sinput<< endl;
                }
            }
        }
    }

    cout << "out building" <<endl;
}

long long doJob1(vector<vector<Content>> & inputMap, vector<Move> &inputMoves) {
    
    int fishX;
    int fishY;
    for(int i = 0; i < inputMap.size(); i++) {
        for(int j = 0; j < inputMap.at(0).size(); j++) {
            if(inputMap.at(i).at(j) == FISH) {
                fishX = j;
                fishY = i;
            }
        }
    }

    visu(inputMap);

    if(verbose) cout << "start moving" << endl;

    for(Move move : inputMoves) {

        if(verbose) cout << "fish in : " << fishX << " " << fishY << endl;

        switch(move) {
            case BOT: {
                if(verbose) cout <<"|"<<endl<<"|"<<endl<<"v"<<endl;
                if(inputMap.at(fishX+1).at(fishY) == NOTHING) {
                    inputMap.at(fishX+1).at(fishY) = FISH;
                    inputMap.at(fishX).at(fishY) = NOTHING;
                    fishX++;
                }
                else if(inputMap.at(fishX+1).at(fishY) == BOX) {
                    int finalx = fishX+1;
                    for(; inputMap.at(finalx).at(fishY) == BOX; finalx++) {}
                    if(inputMap.at(finalx).at(fishY) == NOTHING) {
                        inputMap.at(finalx).at(fishY) = BOX;
                        inputMap.at(fishX+1).at(fishY) = FISH;
                        inputMap.at(fishX).at(fishY) = NOTHING;
                        fishX++;
                    }
                }
            }
            break;
            case TOP: {
                if(verbose) cout <<"^"<<endl<<"|"<<endl<<"|"<<endl;
                if(inputMap.at(fishX-1).at(fishY) == NOTHING) {
                    inputMap.at(fishX-1).at(fishY) = FISH;
                    inputMap.at(fishX).at(fishY) = NOTHING;
                    fishX--;
                }
                else if(inputMap.at(fishX-1).at(fishY) == BOX) {
                    int finalx = fishX-1;
                    for(; inputMap.at(finalx).at(fishY) == BOX; finalx--) {}
                    if(inputMap.at(finalx).at(fishY) == NOTHING) {
                        inputMap.at(finalx).at(fishY) = BOX;
                        inputMap.at(fishX-1).at(fishY) = FISH;
                        inputMap.at(fishX).at(fishY) = NOTHING;
                        fishX--;
                    }
                }
            }
            break;
            case LEFT: {
                if(verbose) cout <<"<---"<<endl;
                if(inputMap.at(fishX).at(fishY-1) == NOTHING) {
                    inputMap.at(fishX).at(fishY-1) = FISH;
                    inputMap.at(fishX).at(fishY) = NOTHING;
                    fishY--;
                }
                else if(inputMap.at(fishX).at(fishY-1) == BOX) {
                    int finaly = fishY-1;
                    for(; inputMap.at(fishX).at(finaly) == BOX; finaly--) {}
                    if(inputMap.at(fishX).at(finaly) == NOTHING) {
                        inputMap.at(fishX).at(finaly) = BOX;
                        inputMap.at(fishX).at(fishY-1) = FISH;
                        inputMap.at(fishX).at(fishY) = NOTHING;
                        fishY--;
                    }
                }
            }
            break;
            case RIGHT: {
                if(verbose) cout <<"--->"<<endl;
                if(inputMap.at(fishX).at(fishY+1) == NOTHING) {
                    inputMap.at(fishX).at(fishY+1) = FISH;
                    inputMap.at(fishX).at(fishY) = NOTHING;
                    fishY++;
                }
                else if(inputMap.at(fishX).at(fishY+1) == BOX) {
                    int finaly = fishY+1;
                    for(; inputMap.at(fishX).at(finaly) == BOX; finaly++) {}
                    if(inputMap.at(fishX).at(finaly) == NOTHING) {
                        inputMap.at(fishX).at(finaly) = BOX;
                        inputMap.at(fishX).at(fishY+1) = FISH;
                        inputMap.at(fishX).at(fishY) = NOTHING;
                        fishY++;
                    }
                }
            }
            break;
        }
        //if(verbose) visu(inputMap);
    }

    long long result = 0;
    for(int i = 0; i < inputMap.size(); i++) {
        for(int j = 0; j < inputMap.at(i).size(); j++) {
            if(inputMap.at(i).at(j) == BOX) {
                result += j + i * 100;
            }
        }
    }

    return result;
}

long long doJob2(vector<vector<Content>> & inputMap, vector<Move> &inputMoves) {
    
    int fishX;
    int fishY;
    for(int i = 0; i < inputMap.size(); i++) {
        for(int j = 0; j < inputMap.at(0).size(); j++) {
            if(inputMap.at(i).at(j) == FISH) {
                fishX = j;
                fishY = i;
            }
        }
    }

    visu(inputMap);

    if(verbose) cout << "start moving" << endl;

    for(Move move : inputMoves) {

        if(verbose) cout << "fish in : " << fishX << " " << fishY << endl;

        switch(move) {
            case BOT: {
                if(verbose) cout <<"|"<<endl<<"|"<<endl<<"v"<<endl;
                if(inputMap.at(fishY+1).at(fishX) == NOTHING) {
                    inputMap.at(fishY+1).at(fishX) = FISH;
                    inputMap.at(fishY).at(fishX) = NOTHING;
                    fishY++;
                }
                else if(inputMap.at(fishY+1).at(fishX) == BOXL || inputMap.at(fishY+1).at(fishX) == BOXR) {
                   Box b; b.lefty = fishY + 1; b.righty = fishY + 1;

                    if(inputMap.at(fishY+1).at(fishX) == BOXL) {
                        b.leftx = fishX;
                        b.rightx = fishX + 1;
                    }
                    else {
                        b.rightx = fishX;
                        b.leftx = fishX - 1;
                    }

                    vector<Box> boxToMove = recurGetBoxesToMove(inputMap, b, BOT);
                    if(!boxToMove.empty()) {
                        for(Box b : boxToMove) {
                            inputMap.at(b.lefty).at(b.leftx) = NOTHING;
                            inputMap.at(b.righty).at(b.rightx) = NOTHING;
                        }
                        for(Box b : boxToMove) {
                            inputMap.at(b.lefty+1).at(b.leftx) = BOXL;
                            inputMap.at(b.righty+1).at(b.rightx) = BOXR;
                        }
                        inputMap.at(fishY+1).at(fishX) = FISH;
                        inputMap.at(fishY).at(fishX) = NOTHING;
                        fishY++;
                    }
                }
            }
            break;
            case TOP: {
                if(verbose) cout <<"^"<<endl<<"|"<<endl<<"|"<<endl;
                if(inputMap.at(fishY-1).at(fishX) == NOTHING) {
                    inputMap.at(fishY-1).at(fishX) = FISH;
                    inputMap.at(fishY).at(fishX) = NOTHING;
                    fishY--;
                }
                else if(inputMap.at(fishY-1).at(fishX) == BOXL || inputMap.at(fishY-1).at(fishX) == BOXR) {
                    Box b; b.lefty = fishY - 1; b.righty = fishY - 1;

                    if(inputMap.at(fishY-1).at(fishX) == BOXL) {
                        b.leftx = fishX;
                        b.rightx = fishX + 1;
                    }
                    else {
                        b.rightx = fishX;
                        b.leftx = fishX - 1;
                    }

                    vector<Box> boxToMove = recurGetBoxesToMove(inputMap, b, TOP);
                    if(!boxToMove.empty()) {
                        for(Box b : boxToMove) {
                            inputMap.at(b.lefty).at(b.leftx) = NOTHING;
                            inputMap.at(b.righty).at(b.rightx) = NOTHING;
                        }
                        for(Box b : boxToMove) {
                            inputMap.at(b.lefty-1).at(b.leftx) = BOXL;
                            inputMap.at(b.righty-1).at(b.rightx) = BOXR;
                        }
                        inputMap.at(fishY-1).at(fishX) = FISH;
                        inputMap.at(fishY).at(fishX) = NOTHING;
                        fishY--;
                    }
                }
            }
            break;
            case LEFT: {
                if(verbose) cout <<"<---"<<endl;
                if(inputMap.at(fishY).at(fishX-1) == NOTHING) {
                    inputMap.at(fishY).at(fishX-1) = FISH;
                    inputMap.at(fishY).at(fishX) = NOTHING;
                    fishX--;
                }
                else if(inputMap.at(fishY).at(fishX-1) == BOXR) {
                    int finalx = fishX-1;
                    for(;inputMap.at(fishY).at(finalx) == BOXR ||
                        inputMap.at(fishY).at(finalx) == BOXL; finalx--) {}
                    if(inputMap.at(fishY).at(finalx) == NOTHING) {
                        for(int xx = fishX-1; xx > finalx - 1; xx--) {
                            if(inputMap.at(fishY).at(xx) == BOXR ||
                                inputMap.at(fishY).at(xx) == NOTHING) inputMap.at(fishY).at(xx) = BOXL;
                            else if(inputMap.at(fishY).at(xx) == BOXL) inputMap.at(fishY).at(xx) = BOXR;
                        }
                        inputMap.at(fishY).at(fishX-1) = FISH;
                        inputMap.at(fishY).at(fishX) = NOTHING;
                        fishX--;
                    }
                }
            }
            break;
            case RIGHT: {
                if(verbose) cout <<"--->"<<endl;
                if(inputMap.at(fishY).at(fishX+1) == NOTHING) {
                    inputMap.at(fishY).at(fishX+1) = FISH;
                    inputMap.at(fishY).at(fishX) = NOTHING;
                    fishX++;
                }
                else if(inputMap.at(fishY).at(fishX+1) == BOXL) {
                    int finalX = fishX+1;
                    for(;inputMap.at(fishY).at(finalX) == BOXR ||
                        inputMap.at(fishY).at(finalX) == BOXL; finalX++) {}
                    if(inputMap.at(fishY).at(finalX) == NOTHING) {
                        for(int xx = fishX+1; xx < finalX + 1;xx++) {
                            if(inputMap.at(fishY).at(xx) == BOXL ||
                                inputMap.at(fishY).at(xx) == NOTHING) inputMap.at(fishY).at(xx) = BOXR;
                            else if(inputMap.at(fishY).at(xx) == BOXR) inputMap.at(fishY).at(xx) = BOXL;
                        }
                        inputMap.at(fishY).at(fishX+1) = FISH;
                        inputMap.at(fishY).at(fishX) = NOTHING;
                        fishX++;
                    }
                }
            }
            break;
        }
    }

    long long result = 0;
    for(int i = 0; i < inputMap.size(); i++) {
        for(int j = 0; j < inputMap.at(i).size(); j++) {
            if(inputMap.at(i).at(j) == BOXL) {
                result += j + i * 100;
            }
        }
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

    while (getline(infile, line)) {
        allLines.push_back(line);
    }

    vector<vector<Content>> inputMap;
    vector<Move> inputMoves;
    
    loopDoStuff(allLines, inputMap, inputMoves);

    result1 = doJob1(inputMap, inputMoves);
    visu(inputMap);
    
    vector<vector<Content>> inputMap2;
    loopDoStuff2(allLines, inputMap2);
    result2 = doJob2(inputMap2, inputMoves);
    visu(inputMap2);


    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}