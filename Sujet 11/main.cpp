#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <math.h>
#include <set>
using namespace std;

static const string filename = "input.txt";
//static const string filename = "example.txt";

vector<long long> loopDoStuff(vector<string> input) {
    vector<long long> result;
    for (string sinput : input) {
        istringstream iss(sinput);
        string s;
        while (getline(iss, s, ' ')) {
            long long val = stoll(s);
            result.push_back(val);
        }
    }
    return result;
}

vector<long long> computeChildrens(long long input) {
    vector<long long> res;
    if(input == 0) res.push_back(1);
    else{
        long long loog = 1 + log10(input) ;
        if(loog % 2 !=0) res.push_back(input * 2024);
        else {
            long long puiss = pow(10, (loog / 2));
            res.push_back(input / puiss);
            res.push_back(input % puiss);
        }
    }
    return res;
}


void visu(vector<long long> input) {
    for(int i =0; i < input.size(); i++) {
        cout << input.at(i) << " ";
    }
    cout << endl;
}

long long part1(vector<long long> input) {

    int maxBlink = 25;
    
    for(int blinkCpt = 0; blinkCpt < maxBlink; blinkCpt++) {
        vector<long long> vec;
        for(int i = 0; i < input.size(); i++) {
            long long inp = input.at(i);

            vector<long long> subvec = computeChildrens(inp);
            vec.insert(vec.end(), subvec.begin(), subvec.end());//append 2 vectors
        }
        input = vec;
    }

    return input.size();
}



struct Caillou {
    long long caillouVal;
    vector<long long> caillouChildrens;
    vector<long long> caillouChildrenCountByGeneration;

    Caillou(){}
    Caillou(long long val) : caillouVal(val) {
        caillouChildrens = computeChildrens(caillouVal);//only call once by each rock
        caillouChildrenCountByGeneration.push_back(caillouChildrens.size());
    }

    void exploreDescendance(map<long long, Caillou*> & caillouIdToCaillou) {

        //each rock ask its child rock how many descendant it got a the right deepness
        //if know we recycle its answer (no cpu used) instead of storing the childrens itself (no ram used)

        int currentLevelKnown = caillouChildrenCountByGeneration.size();
        long long sum = 0;
        for(long long childrendId : caillouChildrens) {
            if(caillouIdToCaillou.find(childrendId) == caillouIdToCaillou.end()) {
                Caillou * nouveauCaillou = new Caillou(childrendId);
                caillouIdToCaillou[childrendId] = nouveauCaillou;
            }

            Caillou * caillouEnfant = caillouIdToCaillou.at(childrendId);

            if(caillouEnfant->caillouChildrenCountByGeneration.size() <= currentLevelKnown - 1) {
                for(int genIndex = caillouEnfant->caillouChildrenCountByGeneration.size(); 
                    genIndex < currentLevelKnown;
                    genIndex++) 
                {
                    //recursively call until we meet expectation
                    caillouEnfant->exploreDescendance(caillouIdToCaillou);
                }
            }
            long long enfantAtGenLessOne = caillouEnfant->caillouChildrenCountByGeneration.at(currentLevelKnown - 1);

            sum += enfantAtGenLessOne;
        }

        caillouChildrenCountByGeneration.push_back(sum);
    }
};

//needed for set of struct Caillou
bool operator<(Caillou const & a, Caillou const & b) {
    return a.caillouVal < b.caillouVal;
}

long long part2(vector<long long> input) {

    //long long type overload after 100, but valid for 75
    int maxBlink = 75;
    long long result = 0;

    set<Caillou *> caillouxInput;
    map<long long, Caillou*> caillouIdToCaillou;

    for(int blinkCpt = 0; blinkCpt < maxBlink; blinkCpt++) {

        vector<long long> vec;
        for(int i = 0; i < input.size(); i++) {
            if(blinkCpt == 0) {
                //first layer, the input
                long long inp = input.at(i);
                Caillou * caillou = new Caillou(inp);
                caillouxInput.insert(caillou);
                caillouIdToCaillou[inp] = caillou;
            }
            else {
                for(Caillou * caillou : caillouxInput) {
                    //ask each input to lookat one step further in its deepness
                    //with each child looking recursively one step further less in its one
                    caillou->exploreDescendance(caillouIdToCaillou);
                }
            }
        }

        result = 0;
        for(int i = 0; i < input.size(); i++) {
            long long caillouId = input.at(i);
            result += caillouIdToCaillou.at(caillouId)->caillouChildrenCountByGeneration.at(blinkCpt);
        }

        cout << "blink  " << blinkCpt << " : " << result<< endl;
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
    
    vector<long long> input = loopDoStuff(allLines);
    result1 = part1(input);
    result2 = part2(input);

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}