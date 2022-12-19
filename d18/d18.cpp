#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <utility>
#include <cassert>
using namespace std;
using ll = int64_t;
using pll = pair<ll, ll>;


//NGL, heavily leverages @jonathanpaulson

class d18 {
public:
    int main_d() {

        ifstream f;
        f.open("d18/test1.txt");
        string line;
        int size = 20;
        vector<vector<vector<char>>> chunk(size, vector<vector<char>>(size, vector<char>(size, 0)));  //change for P2, 0=air, 1=lava, 2=water//false = no cube there

        int xp = 0;
        int yp = 0;
        int zp = 0;
        string tmp;
        int sa = 0;

        while (getline(f, line)) {
            tmp = line.substr(0, line.find(','));
            xp = stoi(tmp);
            line.erase(0, line.find(',') + 1);
            tmp = line.substr(0, line.find(','));
            yp = stoi(tmp);
            line.erase(0, line.find(',') + 1);
            tmp = line;
            zp = stoi(tmp);
            chunk[xp][yp][zp] = 1;

        }

        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                for (int z = 0; z < size; z++) {
                    if (chunk[x][y][z]) {
                        if (x == 0 || !chunk[x - 1][y][z]) {
                            sa++;
                        }
                        if (y == 0 || !chunk[x][y - 1][z]) {
                            sa++;
                        }
                        if (z == 0 || !chunk[x][y][z - 1]) {
                            sa++;
                        }
                        if (x == size-1 || !chunk[x + 1][y][z]) {
                            sa++;
                        }
                        if (y == size-1 || !chunk[x][y + 1][z]) {
                            sa++;
                        }
                        if (z == size-1 || !chunk[x][y][z + 1]) {
                            sa++;
                        }
                    }
                }
            }
        }
        
        cout << "P1: Surface Area: " << sa << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //flow water in from the exterior
        bool done = false;
        while (!done) {  //might need to flow water up into crannies, iterate through space until no water flow
            done = true;
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    for (int z = 0; z < size; z++) {
                        if (chunk[x][y][z] == 0) {
                            if (x == 0 || chunk[x - 1][y][z] == 2) {
                                chunk[x][y][z] = 2;
                                done = false;
                            }
                            if (y == 0 || chunk[x][y - 1][z] == 2) {
                                chunk[x][y][z] = 2;
                                done = false;
                            }
                            if (z == 0 || chunk[x][y][z - 1] == 2) {
                                chunk[x][y][z] = 2;
                                done = false;
                            }
                            if (x == size - 1 || chunk[x + 1][y][z] == 2) {
                                chunk[x][y][z] = 2;
                                done = false;
                            }
                            if (y == size - 1 || chunk[x][y + 1][z] == 2) {
                                chunk[x][y][z] = 2;
                                done = false;
                            }
                            if (z == size - 1 || chunk[x][y][z + 1] == 2) {
                                chunk[x][y][z] = 2;
                                done = false;
                            }
                        }
                    }
                }
            }
        }

        //calculate surface area that touches water
        sa = 0;
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                for (int z = 0; z < size; z++) {
                    if (chunk[x][y][z] == 1) {
                        if (x == 0 || chunk[x - 1][y][z] == 2) {
                            sa++;
                        }
                        if (y == 0 || chunk[x][y - 1][z] == 2) {
                            sa++;
                        }
                        if (z == 0 || chunk[x][y][z - 1] == 2) {
                            sa++;
                        }
                        if (x == size - 1 || chunk[x + 1][y][z] == 2) {
                            sa++;
                        }
                        if (y == size - 1 || chunk[x][y + 1][z] == 2) {
                            sa++;
                        }
                        if (z == size - 1 || chunk[x][y][z + 1] == 2) {
                            sa++;
                        }
                    }
                }
            }
        }

        cout << "P2: Exterior Surface Area: " << sa << endl;

        return 0;
    }
};