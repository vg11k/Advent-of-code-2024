#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

static const string filename = "input.txt";
//static const string filename = "example.txt";

void feedVectors(vector<string> input, vector<vector<int>*>* listToFeed) {

    for (string sinput : input) {
        istringstream iss(sinput);
        string s;
        vector<int> * v = new vector<int>();
        while (getline(iss, s, ' ')) {
            v->push_back(stoi(s));
        }
        listToFeed->push_back(v);
    }
}

vector<bool>* izSafe(vector<int>* mline) {

    bool adjacentValid = true;
    bool incr = true;
    bool decr = true;

    for (int valindex = 1; valindex < mline->size(); valindex++) {
        int val = mline->at(valindex);
        int prevVal = mline->at(valindex - 1);
        int diff = val - prevVal;
        int absdiff = abs(diff);

        if (absdiff < 1 || absdiff > 3) {
            adjacentValid = false;
        }

        if (val > prevVal) {
            decr = false;
        }
        else if (val < prevVal) {
            incr = false;
        }
    }

    vector<bool> * res = new vector<bool>();
    res->push_back(adjacentValid);
    res->push_back(incr);
    res->push_back(decr);

    return res;
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

    vector<vector<int>*>* matrixInput = new vector<vector<int>*>();
    feedVectors(allLines, matrixInput);

    vector<vector<int>*>* unsafeMatrix = new vector<vector<int>*>();

    for (int vectorIndex = 0; vectorIndex < matrixInput->size(); vectorIndex++) {

        vector<int>* mline = matrixInput->at(vectorIndex);

        vector<bool>* safeVector = izSafe(mline);

        bool adjacentValid = safeVector->at(0);
        bool incr = safeVector->at(1);
        bool decr = safeVector->at(2);

        if (adjacentValid && (incr || decr)) {
            result1++;
        }
        else {
            unsafeMatrix->push_back(mline);
        }

        delete safeVector;
    }

    for (int vectorIndex = 0; vectorIndex < unsafeMatrix->size(); vectorIndex++) {

        vector<int>* mline = unsafeMatrix->at(vectorIndex);

        bool safeFound = false;
        for (int i = 0; i < mline->size() && !safeFound; i++) {

            vector<int>* linecpy = new vector<int>();

            for (int j = 0; j < mline->size() && !safeFound; j++) {
                if (i != j) linecpy->push_back(mline->at(j));
            }

            vector<bool>* safeVector = izSafe(linecpy);
            bool adjacentValid = safeVector->at(0);
            bool incr = safeVector->at(1);
            bool decr = safeVector->at(2);

            if (adjacentValid && (incr || decr)) {
                result2++;
                safeFound = true;
            }

            delete linecpy;
            delete safeVector;
        }
    }

    result2 += result1;

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}