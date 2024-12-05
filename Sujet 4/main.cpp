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

vector<string>* generateVerticalLines(vector<string> input) {
    vector<string>* allVerticalLines = new vector<string>();
    for (int i = 0; i < input.at(0).size(); i++) {
        string s = "";
        for (int j = 0; j < input.size(); j++) {
            s += getCharAt(input, i, j);
        }
        allVerticalLines->push_back(s);
    }
    return allVerticalLines;
}

vector<string>* generateDiagsToRight(vector<string> input) {
    vector<string>* allDiagToRightBotLines = new vector<string>();
    for (int i = input.at(0).size() - 1; i > -1; i--) {

        string s = "";

        int ix = i;
        int jy = 0;
        while (ix < input.at(0).size() &&
            jy < input.size()) {

            s += getCharAt(input, ix, jy);

            ix++;
            jy++;
        }

        allDiagToRightBotLines->push_back(s);
    }

    for (int j = 1; j < input.size(); j++) {

        string s = "";
        int ix = 0;
        int jy = j;

        while (ix < input.at(0).size() &&
            jy < input.size()) {

            s += getCharAt(input, ix, jy);

            ix++;
            jy++;
        }

        allDiagToRightBotLines->push_back(s);
    }

    return allDiagToRightBotLines;
}

vector<string>* generateDiagsToLeft(vector<string> input) {
    vector<string>* allDiagToLeftBotLines = new vector<string>();

    for (int i = 0; i < input.size(); i++) {

        string s = "";

        int ix = i;
        int jy = 0;
        while (ix > -1 &&
            jy < input.size()) {

            s += getCharAt(input, ix, jy);

            ix--;
            jy++;
        }

        allDiagToLeftBotLines->push_back(s);
    }

    for (int j = 1; j < input.size(); j++) {

        string s = "";
        int ix = input.at(0).size() - 1;
        int jy = j;

        while (ix < input.at(0).size() &&
            jy < input.size()) {

            s += getCharAt(input, ix, jy);

            ix--;
            jy++;
        }

        allDiagToLeftBotLines->push_back(s);
    }


    return allDiagToLeftBotLines;
}

int occurencesOfInto(vector<string>* input, string seek) {

    int res = 0;

    for (int i = 0; i < input->size(); i++) {        

        string substring = input->at(i);

        //cout << substring << " cherche " << seek << " ";
        int occurence = 0;

        while (substring.size() > 0) {
            int nextSeek = substring.find(seek);
            if (nextSeek > -1) {
                occurence++;
                substring = substring.substr(nextSeek + seek.size(), substring.size());
            }
            else {
                substring = "";
            }
        }

        res += occurence;
        //cout << "found " << occurence << " times" << endl;
    }
    return res;
}

//brute-force fuckit
int bruteForce(vector<string>* verticalInput) {

    int res = 0;


    for (int i = 1; i < verticalInput->at(0).size() - 1; i++) {
        for (int j = 1; j < verticalInput->size() - 1; j++) {
            string a = getCharAt(*verticalInput, i, j);

            if (a == "A") {
                string topLeft = getCharAt(*verticalInput, i-1, j-1);
                string botRight = getCharAt(*verticalInput, i + 1, j + 1);

                if ((topLeft == "M" && botRight == "S") ||
                    (topLeft == "S" && botRight == "M")) {

                    string topRight = getCharAt(*verticalInput, i + 1, j - 1);
                    string botLeft = getCharAt(*verticalInput, i - 1, j + 1);


                        if ((topRight == "M" && botLeft == "S") ||
                            (topRight == "S" && botLeft == "M")) {

                            res++;
                        }
                }
            }
        }
    }

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
    vector<string> allHorizontalLines;

    start = clock();

    while (getline(infile, line)) {
        allHorizontalLines.push_back(line);
    }

    vector<string> * allVerticalLines = generateVerticalLines(allHorizontalLines);
    vector<string> * allDiagToRightBotLines = generateDiagsToRight(allHorizontalLines);
    vector<string> * allDiagToLeftBotLines = generateDiagsToLeft(allHorizontalLines);

    result1 += occurencesOfInto(&allHorizontalLines, "XMAS");
    result1 += occurencesOfInto(&allHorizontalLines, "SAMX");
    result1 += occurencesOfInto(allVerticalLines, "XMAS");
    result1 += occurencesOfInto(allVerticalLines, "SAMX");
    result1 += occurencesOfInto(allDiagToRightBotLines, "XMAS");
    result1 += occurencesOfInto(allDiagToRightBotLines, "SAMX");
    result1 += occurencesOfInto(allDiagToLeftBotLines, "XMAS");
    result1 += occurencesOfInto(allDiagToLeftBotLines, "SAMX");

    result2 = bruteForce(&allHorizontalLines);



    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}