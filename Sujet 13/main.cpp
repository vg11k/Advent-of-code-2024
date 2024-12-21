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

string getCharAt(vector<string> s, long long x, long long y) {
    return s.at(y).substr(x, 1);
}

struct Coords {
    long long x;
    long long y;
};

struct Button {
    string letter;
    Coords * move;
    Button(string s) : letter(s) {move = new Coords();}
};

struct Machine {
    Button * b1;
    Button * b2;
    Coords * token;
    Machine() {
        token = new Coords();
    }

    Coords getBestConfig() {

        Coords res;
        res.x = -1;
        res.y = -1;

        long long nbPushX = 0;
        long long nbPushY = 0;

        long long bx1 = b1->move->x;
        long long bx2 = b1->move->y;
        long long by1 = b2->move->x;
        long long by2 = b2->move->y;
        long long tx = token->x;
        long long ty = token->y;

        nbPushY = ((bx1 * ty) - (bx2 * tx)) / ((bx1 * by2) - (by1 * bx2));
        nbPushX = (tx - (by1 * nbPushY)) / bx1;

        cout << "titi" << endl;

        /*cout << tx << " " << by1 << " " << bx1 << endl;
        cout << ty << " " << by2 << " " << bx2 << endl;
        cout << nbPushY << " " << nbPushX << endl;*/

        if(nbPushY > -1 && nbPushX > -1 /*&& nbPushY < 101 && nbPushX < 101*/) {

            long long verifx = nbPushX * bx1 + nbPushY * by1;
            long long verify = nbPushX * bx2 + nbPushY * by2;

            cout << "candidat" << endl;

            //cout << verifx << " " << verify << endl;

            if(verifx == tx && verify == ty) {
                //cout << nbPushX << " " << nbPushY << " valid" << endl;
                res.x = nbPushX;
                res.y = nbPushY;
            }
            else {
                cout << "candidat invalide : " <<verifx << " " << tx << " " << verify << " " << ty << endl;
            }
        } 
        return res;   
    }
};

vector<Machine *> loopDoStuff(vector<string> input) {

    vector<Machine *> result;

    for (long long i = 0; i < input.size(); i = i + 4) {
        string b1s = input.at(i);
        string b2s = input.at(i+1);
        string tokens = input.at(i+2);

        Button * b1 = new Button("X");
        Button * b2 = new Button("Y");
        Machine * mach = new Machine();
        mach->b1 = b1;
        mach->b2 = b2;

        istringstream iss(b1s);
        string s;
        getline(iss, s, ' ');
        b1->move->x = stoi(s);
        getline(iss, s, ' ');
        b1->move->y = stoi(s);

        iss = istringstream(b2s);
        getline(iss, s, ' ');
        b2->move->x = stoi(s);
        getline(iss, s, ' ');
        b2->move->y = stoi(s);

        iss = istringstream(tokens);
        getline(iss, s, ' ');
        mach->token->x = stoll(s);
        getline(iss, s, ' ');
        mach->token->y = stoll(s);

        result.push_back(mach);
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

    vector<Machine*> machines = loopDoStuff(allLines);
    vector<Coords> coords;

    for(Machine * machine : machines) {
        coords.push_back(machine->getBestConfig());
    }

    for(Coords c : coords) {
        if(c.x > -1 && c.y > -1) {
            result1 += c.x * 3 + c.y;
        }
    }

    for(Machine * machine : machines) {
        machine->token->x += 10000000000000;
        machine->token->y += 10000000000000;
    }

    coords = vector<Coords>();

    for(Machine * machine : machines) {
        coords.push_back(machine->getBestConfig());
    }

    for(Coords c : coords) {
        if(c.x > -1 && c.y > -1) {
            result2 += c.x * 3 + c.y;
        }
    }




    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}