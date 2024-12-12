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

long long part1(vector<string> allLines) {

    int datasize = 14;

    int combinationCount = pow(2, datasize - 1);
    vector<vector<int>> operations;
    for (int j = 0; j < combinationCount; j++) {
        vector<int> operationLine;
        for (int i = 0; i < datasize - 1; i++) {
            operationLine.push_back(0);
        }

        for (int i = 0; i < j; i++) {
            bool stop = false;
            operationLine[0]++;
            for (int k = 0; k < operationLine.size() - 1; k++)
                if (operationLine[k] > 1) {
                    operationLine[k] = 0;
                    operationLine[k + 1]++;
                }
        }

        operations.push_back(operationLine);
    }

   // cout << "combinaisons generees" << endl;

    long long result1 = 0;

    for (string line : allLines) {

        long long objective = -1;
        vector<long long> data;

        istringstream iss(line);
        string s;
        while (getline(iss, s, ' ')) {
            long long val = stoll(s);
            if (objective < 0) objective = val;
            else data.push_back(val);
        }

        int localCombinationCount = pow(2, data.size() - 1);
        bool valid = false;
        for (int i = 0; i < localCombinationCount && !valid; i++) {

            long long localResult = data.at(0);
            for (int j = 1; j < data.size(); j++) {

                long long operation = operations.at(i).at(j - 1);
                long long valueToOperate = data.at(j);

                if (operation == 0) {
                    localResult += valueToOperate;
                }
                else localResult *= valueToOperate;
            }

            if (localResult == objective) {
                result1 += objective;
                valid = true;
            }
        }
    }

    return result1;
}

long long part2(vector<string> allLines) {



    int datasize = 13;

    long long combinationCount = pow(3, datasize - 1);
    vector<vector<int>> operations;
    for (long j = 0; j < combinationCount; j++) {
        vector<int> operationLine;
        for (int i = 0; i < datasize - 1; i++) {
            operationLine.push_back(0);
        }

        for (long i = 0; i < j; i++) {
            bool stop = false;
            operationLine[0]++;
            for (int k = 0; k < operationLine.size() - 1; k++)
                if (operationLine[k] > 2) {
                    operationLine[k] = 0;
                    operationLine[k + 1]++;
                }
        }

        /*for (int i = 0; i < operationLine.size(); i++)
            cout << operationLine.at(i);
        cout << endl;*/

        if (j % 50000 == 0)cout << j << endl;

        operations.push_back(operationLine);
    }

    cout << "combinaisons generees" << endl;

    long long result2 = 0;

    for (string line : allLines) {

        long long objective = -1;
        vector<long long> data;

        istringstream iss(line);
        string s;
        while (getline(iss, s, ' ')) {
            long long val = stoll(s);
            if (objective < 0) objective = val;
            else data.push_back(val);
        }

        long long localCombinationCount = pow(3, data.size() - 1);
        bool valid = false;
        for (int i = 0; i < localCombinationCount && !valid; i++) {

            long long localResult = data.at(0);
            for (int j = 1; j < data.size(); j++) {

                long long operation = operations.at(i).at(j - 1);
                long long valueToOperate = data.at(j);

                if (operation == 0) {
                    localResult += valueToOperate;
                }
                else if(operation == 1) {
                    if (valueToOperate < 10) localResult *= 10;
                    else if (valueToOperate < 100) localResult *= 100;
                    else if (valueToOperate < 1000) localResult *= 1000;
                    else if (valueToOperate < 10000) localResult *= 10000;

                    localResult += valueToOperate;
                }
                else localResult *= valueToOperate;
            }

            if (localResult == objective) {
                result2 += objective;
                valid = true;
            }
        }
    }

    return result2;
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

    result1 = part1(allLines);
    result2 = part2(allLines);



    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}