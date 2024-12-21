#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include<set>
using namespace std;

static const string filename = "input.txt";
//static const string filename = "example.txt";

string getCharAt(vector<string> s, int x, int y) {
    return s.at(y).substr(x, 1);
}

struct Slot{ 
    int x;
    int y;
    int z;
    vector<Slot*> to;
    vector<Slot*> uselessVector;//go faster with an empty vector at exec for some weird reason. #dark stuff
    Slot(int a, int b, int c) : x(a), y(b), z(c) {}

    int recur(set<Slot*> * dests) {

        int res = 0;
        for(Slot * child : to) res += child->recur(dests);
        
        if(z == 9) {
            res++;
            dests->insert(this);
        }

        return res;
    }

    void exploreOneDirection(set<Slot*> & setiplusone, vector<vector<Slot*>> slots, int xmodificator, int ymodificator) {
        Slot * ss = slots.at(x + xmodificator).at(y + ymodificator);
        if(ss->z == z + 1) {
            setiplusone.insert(ss);
            to.push_back(ss);
        }
    }

    void exploreAll(set<Slot*> & setiplusone, vector<vector<Slot*>> & slots, vector<string> & allLines) {
            if(x > 0) exploreOneDirection(setiplusone, slots, -1, 0);
            if(x < allLines.at(0).size() -1) exploreOneDirection(setiplusone,  slots, 1, 0);
            if(y > 0) exploreOneDirection(setiplusone,  slots, 0, -1);
            if(y < allLines.size() -1) exploreOneDirection(setiplusone, slots, 0, 1);
    }
};


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

    vector<vector<Slot*>> slots;

    while (getline(infile, line)) {
        allLines.push_back(line);
    }

    set<Slot*> allZeros;

    for(int i = 0; i < allLines.size(); i++) {
        for(int j = 0; j < allLines.at(0).size(); j++) {
            if(i == 0) slots.push_back(vector<Slot*>());
            Slot * s = new Slot(j, i, stoi(getCharAt(allLines, j, i)));
            slots.at(j).push_back(s);
            if(s->z == 0)
                allZeros.insert(s);
        }
    }

    vector<set<Slot*>> allSlotPathsToExplore;
    allSlotPathsToExplore.push_back(allZeros);
    bool change = true;
    
    while(change) {
        change = false;
        set<Slot*> seti = allSlotPathsToExplore.back();
        set<Slot*> setiplusone;

        for(Slot * si : seti)  si->exploreAll(setiplusone, slots, allLines);

        if(setiplusone.size() > 0) {
            allSlotPathsToExplore.push_back(setiplusone);
            if((*setiplusone.begin())->z != 9) change = true;
        }
    }

    for(Slot * slot : allZeros) {
        set<Slot *> * destinations = new set<Slot*>();
        int recurr = slot->recur(destinations);
        result1 += destinations->size();
        delete destinations;
        result2 += recurr;
    }

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}