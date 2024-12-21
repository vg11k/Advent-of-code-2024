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

struct Robot {
    long long posx;
    long long posy;

    long long movx;
    long long movy;

    int flatpos;

    void move(long long seconds,int wide, int tall) {

        posx += movx * seconds;
        posy += movy * seconds;

        posx %= wide;
        posy %= tall;
        if (posx < 0) posx += wide;
        if (posy < 0) posy += tall;

        flatpos = posx + posy * wide;
        //cout << posx << " " << posy << endl;

    }
};

vector<Robot*> loopDoStuff(vector<string> input) {
    vector<Robot*> results;
    for (string sinput : input) {

        Robot* r = new Robot();
        results.push_back(r);
        istringstream iss(sinput);
        string s;
        getline(iss, s, ' ');
        r->posx = stoll(s);
        getline(iss, s, ' ');
        r->posy = stoll(s);
        getline(iss, s, ' ');
        r->movx = stoll(s);
        getline(iss, s, ' ');
        r->movy = stoll(s);
    }
    return results;
}

void visu(vector<Robot*> robots, int wide, int tall) {

    map<string, int> posToCoords;
    for (Robot* r : robots) {
        string key = to_string(r->posx) + " " + to_string(r->posy);
        if (posToCoords.find(key) == posToCoords.end()) {
            posToCoords[key] = 0;
        }
        posToCoords[key]++;
    }

    for (long long i = 0; i < tall; i++) {
        for (long long j = 0; j < wide; j++) {
            string key = to_string(j) + " " + to_string(i);
            if (posToCoords.find(key) == posToCoords.end()) cout << ".";
            else cout << posToCoords[key];
        }
        cout << endl;
    }
 }

void printMyVector(long long frameId, vector<vector<int>> monvec, const int w, const int h) {

    int red [101][103];
    int green[101][103];
    int blue[101][103];

    FILE* f;
    unsigned char* img = NULL;
    int filesize = 54 + 3 * w * h;

    img = (unsigned char*)malloc(3 * w * h);
    memset(img, 0, 3 * w * h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            int x = i, y = (h - 1) - j;
            int r = 0;
            int g = 0;
            int b = 0;
            if (monvec.at(i).at(j) == 1) {
                r = 255;
                g = 255;
                b = 255;
            }

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            img[(x + y * w) * 3 + 2] = (unsigned char)(r);
            img[(x + y * w) * 3 + 1] = (unsigned char)(g);
            img[(x + y * w) * 3 + 0] = (unsigned char)(b);
        }
    }

    unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
    unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
    unsigned char bmppad[3] = { 0,0,0 };

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);


    string filename = "ct/" + to_string(frameId) + ".bmp";
    f = fopen(filename.c_str(), "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);

    for (int i = 0; i < h; i++)
    {
        fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
    }

    free(img);
    fclose(f);


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


    vector<Robot*> robots = loopDoStuff(allLines);

    int wide = 101;
    int tall = 103;

    for (Robot* r : robots) r->move(100, wide, tall);



    //visu(robots, wide, tall);


    int a =0, b=0, c=0, d=0;
    long long widequad = ((wide - 1) / 2);
    long long tallquad = ((tall - 1) / 2);

    //cout << "quads : " << widequad << " " << tallquad << endl;

    for (Robot* r : robots) {
        if (r->posx < widequad && r->posy < tallquad) a++;
        if (r->posx > widequad && r->posy < tallquad) b++;
        if (r->posx < widequad && r->posy > tallquad) c++;
        if (r->posx > widequad && r->posy > tallquad) d++;
    }

    //cout << a << " " << b << " " << c << " " << d << endl;

    result1 = a * b * c * d;

    for (Robot* r : robots) delete r;

    robots = loopDoStuff(allLines);

    vector<vector<int>> monvector;
    for (int i = 0; i < wide; i++) {
        for (int j = 0; j < tall; j++) {
            monvector.push_back(vector<int>());

            monvector.at(i).push_back(0);
        }
    }

    //rip your hdd
    for(long long frameId = 1; frameId < 100000; frameId++) {

        for (int i = 0; i < wide; i++) {
        for (int j = 0; j < tall; j++) {
                monvector.at(i).at(j) = 0;
            }
        }
        
        for (Robot* r : robots) {
            r->move(1, wide, tall);
            monvector.at(r->posx).at(r->posy) = 1;
        }

        printMyVector(frameId, monvector, wide, tall);

    }



    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}