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


bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
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
        cout << line << endl;
    }

    //isolate all between "mul" instructions
    
    string seek = "mul";
    vector<string> allSeekString;
    for (string line : allLines) {
        string substring = line;
        while (substring.size() > 0) {
            int nextMul = substring.find(seek);
            string res = "";
            if (nextMul > -1) {
                res = substring.substr(0, nextMul);
                substring = substring.substr(nextMul + seek.size(), substring.size());
            }
            else {
                res = substring;
                substring = "";
            }
            allSeekString.push_back(res);
        }
    }

    for (string mulElement : allSeekString) {

        //isolate valide input format to cast and compute
        if (mulElement.substr(0, 1) == "(") {
            if (mulElement.find(")") > 0) {
                string content = mulElement.substr(1, mulElement.find(")"));
                if (content.find(",") > 0) {

                    try {
                        istringstream iss(content);
                        string s;

                        bool isnum = true;

                        getline(iss, s, ',');

                        isnum &= is_number(s);
                        int i1 = stoi(s);

                        getline(iss, s, ')');

                        isnum &= is_number(s);
                        int i2 = stoi(s);

                        if (isnum) {

                            result1 += i1 * i2;
                        }
                    }
                    catch (const invalid_argument e) {
                        //stfu
                    }
                }
            }
            
        }

    }

    bool izEnabled = true;

    for (string mulElement : allSeekString) {

        if (izEnabled) {

            //isolate valide input format to cast and compute
            if (mulElement.substr(0, 1) == "(") {
                if (mulElement.find(")") > 0) {
                    string content = mulElement.substr(1, mulElement.find(")"));
                    if (content.find(",") > 0) {

                        try {
                            istringstream iss(content);
                            string s;

                            bool isnum = true;

                            getline(iss, s, ',');

                            isnum &= is_number(s);
                            int i1 = stoi(s);

                            getline(iss, s, ')');

                            isnum &= is_number(s);
                            int i2 = stoi(s);

                            if (isnum) {

                                result2 += i1 * i2;
                            }
                        }
                        catch (const invalid_argument e) {
                            //stfu
                        }
                    }
                }
            }
        }

        //easier to seek the last if instead we simply seek the first

        string revstring = mulElement;
        reverse(revstring.begin(), revstring.end());

        int dopos = revstring.find(")(od");
        int dontpos = revstring.find(")(t'nod");

        if (dopos > -1 && dontpos > -1) {
            if(dopos > dontpos) izEnabled = false;
            else izEnabled = true;
        }
        else if (dopos > -1 && !izEnabled) izEnabled = true;
        else if (dontpos > -1 && izEnabled)izEnabled = false;
    }



    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}