#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <omp.h>
using namespace std;
static const string filename = "input.txt";
//static const string filename = "example.txt";
int main(char * args[]) {
    std::cout<< "Hello World !" << endl;
    cout << "using input " << filename << endl;
    clock_t start, end;
    ifstream infile(filename);
    string line;
    long long result1 = 0;
    long long result2 = 0;
    vector<string> allLines;
    start = clock();
    while(getline(infile, line)) {
        allLines.push_back(line);
    }
    map<int, vector<int>*> pagemap;
    vector<vector<int>*> pagelists;
    bool stop = false;
    vector<int> allIn;
    vector<int> allOut;
    for(int lineIndex = 0; lineIndex < allLines.size(); lineIndex++) {
        string line = allLines.at(lineIndex);
        if(allLines.at(lineIndex) == "") {
            stop = true;
        }
        else if(!stop) {
            istringstream iss(line);
            string a;
            getline(iss, a, '|');
            string b;
            getline(iss, b, '|');
            int ia = stoi(a);
            int ib = stoi(b);
            allIn.push_back(ia);
            allOut.push_back(ib);
            if(pagemap.find(ia) == pagemap.end()) {
                pagemap[ia] = new vector<int>();
            }
            pagemap[ia]->push_back(ib);
        }
        else {
            vector<int> * pages = new vector<int>();
            istringstream iss(line);
            string s;
            while(getline(iss,s,',')) {
                pages->push_back(stoi(s));
            }
            pagelists.push_back(pages);
        }
    }
    for(vector<int> * pages : pagelists) {
        bool valid = true;
        for(int i = 0; i < pages->size() - 1; i++) {
            int p1 = pages->at(i);
            for(int j = i+1; j < pages->size(); j++) {
                int p2 = pages->at(j);
                vector<int> * p2vector = pagemap[p2];
                if(p2vector != NULL) {
                    for(int k = 0; k < p2vector->size(); k++) {
                        
                        if(p2vector->at(k) == p1) {
                            valid = false;
                        }
                    }
                }
            }
        }
        if(valid) {
            int middle = pages->at(pages->size() / 2);
            result1 += middle;
        }
        else {
            //part 2
            vector<int> correctedPages;
            while(pages->size() > 0) {
                int winner = 0;
                vector<int> * winnerList = pagemap[pages->at(winner)];
                for(int i = 1; i < pages->size(); i++) {
                    if(pagemap.find(pages->at(i)) != pagemap.end()) {
                        vector<int> * ilist = pagemap[pages->at(i)];
                        if(ilist != NULL) {
                            for(int j = 0; j < ilist->size(); j++) {
                                if(winnerList != NULL) {
                                    if(ilist->at(j) == pages->at(winner)) {
                                        winner = i;
                                        winnerList = ilist;
                                    }
                                }
                                else {
                                    winner = i;
                                    winnerList = ilist;
                                }
                            }
                        }
                    }
                }
                correctedPages.push_back(pages->at(winner));
                pages->erase(pages->begin() + winner);
            }
            int middle = correctedPages.at(correctedPages.size() / 2);
            result2 += middle;
        }
    }
    end = clock();
    std::cout << "result 1 : " << result1 << endl;
    std::cout << "result 2 : " << result2 << endl; //6173 too high
    std::cout << end - start << " ms to compute." << endl;
    std::cout << "Bye World !" << endl;
    return 0;
}