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

void insertSort(vector<int>* listToInsert, int val) {

    if (listToInsert->size() == 0) listToInsert->push_back(val);
    else {
        int indexToInsert = -1;
        for (int i = 0; i < listToInsert->size() && indexToInsert < 0; i++) {
            if (listToInsert->at(i) > val) {
                indexToInsert = i;
            }
        }
        if (indexToInsert < 0) listToInsert->push_back(val);
        else listToInsert->insert(listToInsert->begin() + indexToInsert, val);
    }
}

void feedVectors(vector<string> input, vector<int>* leftList, vector<int>* rightList) {

    for (string sinput : input) {
        istringstream iss(sinput);
        string s;
        getline(iss, s, ' ');
        insertSort(leftList, stoi(s));
        getline(iss, s, ' ');
        getline(iss, s, ' ');
        getline(iss, s, ' ');
        insertSort(rightList, stoi(s));
    }
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

    vector<int>* leftList = new vector<int>();
    vector<int>* rightList = new vector<int>();

    feedVectors(allLines, leftList, rightList);
    for (int i = 0; i < allLines.size(); i++) {
        result1 += abs(leftList->at(i) - rightList->at(i));
    }

    map<int, int> leftToRightIt;
    for (int i = 0; i < leftList->size(); i++) {
        int leftVal = leftList->at(i);
        if (leftToRightIt.find(leftVal) == leftToRightIt.end()) {
            int cpt = 0;
            for (int j = 0; j <= leftVal && j < rightList->size(); j++) {
                if (rightList->at(j) == leftVal) {
                    cpt++;
                }
            }
            leftToRightIt[leftVal] = cpt;
        }
    }

    for (int i = 0; i < leftList->size(); i++) {
        result2 += leftList->at(i) * leftToRightIt[leftList->at(i)];
    }


    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}