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

void visu(vector<int> data) {
    for (int i = 0; i < data.size(); i++) {
        if (data.at(i) == -1)cout << ".";
        else cout << data.at(i);
    }
    cout << endl;
}


long long part1(vector<int> input) {

    vector<int> transfo;
    vector<int> dataWithoutNil;

    for (int i = 0; i < input.size(); i++) {

        int digit = (i / 2);

        if (i % 2 != 0) {
            digit = -1;
        }

        for (int j = 0; j < input.at(i); j++) {
            transfo.push_back(digit);
            if (digit != -1) dataWithoutNil.push_back(digit);
        }
    }

    int cptNil = 0;

    for (int i = 0; i < transfo.size(); i++) {
        if (transfo.at(i) < 0) {            
            transfo.at(i) = dataWithoutNil.at(dataWithoutNil.size() - 1);
            dataWithoutNil.pop_back();
            cptNil++;
        }
    }

    for (int i = 0; i < cptNil; i++) {
        transfo.pop_back();
    }  

    long long checksum = 0;

    for (int i = 0; i < transfo.size(); i++) {
        checksum += i * transfo.at(i);
    }

    return checksum;
}

struct File {
    vector<int> content;
    int origin;
};

long long part2(vector<int> input) {

    vector<int> transfo;
    vector<File> files;

    for (int i = 0; i < input.size(); i++) {

        int digit = (i / 2);

        if (i % 2 != 0) {
            digit = -1;
        }

        File localFile;
        for (int j = 0; j < input.at(i); j++) {
            transfo.push_back(digit);
            if (digit != -1) localFile.content.push_back(digit);
        }
        localFile.origin = transfo.size() - localFile.content.size();
        files.push_back(localFile);
    }


    reverse(files.begin(), files.end());

    for (File file : files) {

        int fileSize = file.content.size();
        bool found = 0;


        for (int i = 0; i < transfo.size() && !found && i < file.origin; i++) {

            if (transfo.at(i) < 0) {

                int spaceSize = 1;
                for (int j = i+1; j < transfo.size() && transfo.at(j) == -1; j++) spaceSize++;

                if (spaceSize >= fileSize) {

                    found = true;
                    for (int j = 0; j < fileSize; j++) {
                        transfo.at(i + j) = file.content.at(j);
                    }


                    for (int j = 0; j < fileSize; j++) {
                        transfo.at(file.origin + j) = -1;
                    }
                }
            }
        }
        
    }

    long long checksum = 0;

    for (int i = 0; i < transfo.size(); i++) {
       if(transfo.at(i) > -1)
            checksum += i * transfo.at(i);
    }

    return checksum; //2858 obj
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

    vector<int> array;
    
    for (int i = 0; i < allLines.at(0).size(); i++) {
        array.push_back(stoll(allLines.at(0).substr(i,1)));
    }

    result1 = part1(array);
    result2 = part2(array);

    end = clock();


    //example 1928 ok
    cout << "result1 : " << result1 << endl; //6301895872542

    //example 2858
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}