#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <algorithm> 
using namespace std;

//static const string filename = "input.txt";
static const string filename = "example.txt";

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

struct Plot {
    int x;
    int y;
    string plant;
    vector<Plot*> voisins;
    vector<Plot*> voisinsWDiags;
    vector<Plot*> voisinsDiags;
    Plot(int a, int b, string s) : x(a), y(b), plant(s) {
        voisins = vector<Plot*>();
        voisinsWDiags = vector<Plot*>();
    }
};

bool operator<(const Plot& a, const Plot& b)
{
    return a.x * 1000 + a.y < b.x * 1000 + b.y;
}

bool comparePtrToNode(Plot* a, Plot* b) {
    return a->x * 1000 + a->y < b->x * 1000 + b->y;
}
bool comparePtrToNode2(Plot* a, Plot* b) {
    return a->y * 1000 + a->x < b->y * 1000 + b->x;
}

/*
bool operator<(const Plot * a, const Plot * b)
{
    return a->x * 1000 + a->y < b->x * 1000 + b->y;
}*/

enum Direction { TOP, RIGHT, BOT, LEFT};

struct Region {
    set<Plot*> content;
    string plant;
    Region() {
        plant = "NOPE";
        content = set<Plot*>();
    }

    long long computePerimeter(vector<vector<Plot*>>& plotGrid) {
        long long res = 0;
        for (Plot* p : content) {
            for (Plot* vp : p->voisins) {
                if (content.find(vp) == content.end()) {
                    res++;
                }
            }

            if (p->x == 0 || p->x == plotGrid.at(0).size() - 1) {
                res++;
            }

            if (p->y == 0 || p->y == plotGrid.size() - 1) {
                res++;
            }

        }
        return res;
    }


    long long ray() {

        long long result = 0;

        map<Direction, vector<Plot*>> mamap;
        mamap[TOP] = vector<Plot*>();
        mamap[BOT] = vector<Plot*>();
        mamap[RIGHT] = vector<Plot*>();
        mamap[LEFT] = vector<Plot*>();

        map<string, Plot*> keyToPlot;



        //boite englobante
        int maxx = -100;
        int minx = 200;
        int maxy = -100;
        int miny = 200;

        for (Plot* p : content) {
            if (p->x > maxx)maxx = p->x;
            if (p->x < minx)minx = p->x;
            if (p->y > maxy)maxy = p->y;
            if (p->y < miny)miny = p->y;

            keyToPlot[to_string(p->x) + " " + to_string(p->y)] = p;
        }

        minx--;
        miny--;
        maxx++;
        maxy++;

        //from right
        for (int i = minx; i < maxx; i++) {
            for (Plot* p : content) {
                string prevKey = to_string(p->x - 1) + " " + to_string(p->y);
                if (p->x - 1 == i && keyToPlot.find(prevKey) == keyToPlot.end()) {
                    mamap[RIGHT].push_back(p);
                }
            }
        }

        //from left
        for (int i = maxx; i > minx; i--) {
            for (Plot* p : content) {
                string prevKey = to_string(p->x + 1) + " " + to_string(p->y);
                if (p->x + 1 == i && keyToPlot.find(prevKey) == keyToPlot.end()) {
                    mamap[LEFT].push_back(p);
                }
            }
        }

        //from top
        for (int i = miny; i < maxy; i++) {
            for (Plot* p : content) {
                string prevKey = to_string(p->x) + " " + to_string(p->y - 1);
                if (p->y - 1 == i && keyToPlot.find(prevKey) == keyToPlot.end()) {
                    mamap[TOP].push_back(p);
                }
            }
        }

        //from bot
        for (int i = maxy ; i > miny; i--) {
            for (Plot* p : content) {
                string prevKey = to_string(p->x) + " " + to_string(p->y + 1);
                if (p->y + 1 == i && keyToPlot.find(prevKey) == keyToPlot.end()) {
                    mamap[BOT].push_back(p);
                }
            }
        }

       // cout << maxx << " " << minx << " " << maxy << " " << miny << endl;
       // cout << mamap[RIGHT].size() << " " << mamap[LEFT].size() << " " << mamap[TOP].size() << " " << mamap[BOT].size() << endl;

        sort(mamap[RIGHT].begin(), mamap[RIGHT].end(), comparePtrToNode);
        sort(mamap[LEFT].begin(), mamap[LEFT].end(), comparePtrToNode);
        sort(mamap[TOP].begin(), mamap[TOP].end(), comparePtrToNode2);
        sort(mamap[BOT].begin(), mamap[BOT].end(), comparePtrToNode2);

        Plot* prev = NULL;
        for (Plot * p : mamap[RIGHT]) {
            if (prev == NULL || prev->x != p->x || prev->y != p->y - 1) {
                result++;
            }
            prev = p;
        }

        prev = NULL;
        for (Plot* p : mamap[LEFT]) {
            if (prev == NULL || prev->x != p->x || prev->y != p->y - 1) {
                result++;
            }
            prev = p;
        }

        prev = NULL;
        for (Plot* p : mamap[TOP]) {
            if (prev == NULL || prev->y != p->y || prev->x != p->x - 1) {
                result++;
            }
            prev = p;
        }

        prev = NULL;
        for (Plot* p : mamap[BOT]) {
            //cout << p->x << " " << p->y << endl;
            if (prev == NULL || prev->y != p->y || prev->x != p->x - 1) {
                result++;
            }
            prev = p;
        }
       

        return result;
    }
};

void handleFile(string s) {

    ifstream infile(s);
    string line;
    long long result1 = 0;
    long long result2 = 0;
    vector<string> allLines;


    while (getline(infile, line)) {
        allLines.push_back(line);
    }

    vector<vector<string>> grid;
    vector<vector<Plot*>> plotGrid;
    set<Plot*> plotsRemainingToSort;


    for (int lineId = 0; lineId < allLines.size(); lineId++) {
        for (int colId = 0; colId < allLines.at(lineId).size(); colId++) {
            string plant = getCharAt(allLines, colId, lineId);
            if (lineId == 0) {
                grid.push_back(vector<string>());
                plotGrid.push_back(vector<Plot*>());
            }
            grid.at(colId).push_back(plant);
            Plot* plotptr = new Plot(colId, lineId, plant);
            plotGrid.at(colId).push_back(plotptr);
            plotsRemainingToSort.insert(plotptr);
        }
    }

    vector<Region*> regions;

    while (!plotsRemainingToSort.empty()) {

        Plot* rootPlot = *plotsRemainingToSort.begin();


        Region* region = new Region();
        region->content.insert(rootPlot);
        region->plant = rootPlot->plant;

        regions.push_back(region);

        plotsRemainingToSort.erase(rootPlot);

        bool newFound = true;
        while (newFound) {
            newFound = false;

            for (Plot* plot : region->content) {
                vector<Plot*> neibourghs;
                vector<Plot*> neibourghsDiag;

                if (plot->x > 0) {
                    Plot* p = plotGrid.at(plot->x - 1).at(plot->y);
                    neibourghs.push_back(p);
                }
                if (plot->x < allLines.at(0).size() - 1) {
                    Plot* p = plotGrid.at(plot->x + 1).at(plot->y);
                    neibourghs.push_back(p);

                }
                if (plot->y > 0) {
                    Plot* p = plotGrid.at(plot->x).at(plot->y - 1);
                    neibourghs.push_back(p);

                }
                if (plot->y < allLines.size() - 1) {
                    Plot* p = plotGrid.at(plot->x).at(plot->y + 1);
                    neibourghs.push_back(p);
                }

                if (plot->x > 0 && plot->y > 0) {
                    Plot* p = plotGrid.at(plot->x - 1).at(plot->y - 1);
                    neibourghsDiag.push_back(p);
                }
                if (plot->x < allLines.at(0).size() - 1 && plot->y > 0) {
                    Plot* p = plotGrid.at(plot->x + 1).at(plot->y - 1);
                    neibourghsDiag.push_back(p);
                }
                if (plot->x > 0 && plot->y < allLines.size() - 1) {
                    Plot* p = plotGrid.at(plot->x - 1).at(plot->y + 1);
                    neibourghsDiag.push_back(p);
                }
                if (plot->x < allLines.at(0).size() - 1 && plot->y < allLines.size() - 1) {
                    Plot* p = plotGrid.at(plot->x + 1).at(plot->y + 1);
                    neibourghsDiag.push_back(p);
                }

                if (plot->voisins.empty()) {
                    for (Plot* p : neibourghs) {
                        plot->voisins.push_back(p);
                        plot->voisinsWDiags.push_back(p);
                    }
                    for (Plot* p : neibourghsDiag) {
                        plot->voisinsWDiags.push_back(p);
                        plot->voisinsDiags.push_back(p);
                    }
                }

                for (Plot* p : neibourghs) {
                    if (p->plant == region->plant && plotsRemainingToSort.find(p) != plotsRemainingToSort.end()) {
                        newFound = true;
                        region->content.insert(p);
                        plotsRemainingToSort.erase(p);
                    }
                }
            }
        }
    }



    for (Region* r : regions) {
        result1 += r->computePerimeter(plotGrid) *r->content.size();
        result2 += r->ray() * r->content.size();
    }


    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
}

int main(char* args[]) {

    cout << "Hello World !" << endl;

    bool debug = false;

    clock_t start, end;

    start = clock();

    string s = filename.c_str();

   /* handleFile(s + "-1");
    cout << "target 80" << endl;
    handleFile(s + "-2");
    cout << "target 436" << endl;
    handleFile(s + "-3");
    cout << "target 236" << endl;
    handleFile(s + "-4");
    cout << "target 368" << endl;
    handleFile(s + "-5");
    cout << "target 1206" << endl;*/

    handleFile("input.txt");
    
    
    end = clock();
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}