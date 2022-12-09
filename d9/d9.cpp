#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class d9 {
public:
    int main_d() {
        ifstream f;
        f.open("d9/test1.txt");
        string line;
        int size = 1000;
        int hx = size/2;
        int hy = size/2;
        int tx = size/2;
        int ty = size/2;
        vector<vector<int>> array(size, vector<int>(size, 0));

        char dir;
        int num;

        while (getline(f, line)) {
            dir = line[0];
            line.erase(0, line.find(' ') + 1);
            num = stoi(line);
            for (int i = 0; i < num; i++) {
                if (dir == 'R') {
                    hx++;
                    cout << "RIGHT " << hx<<":"<< hy << endl;
                }
                if (dir == 'L') {
                    hx--;
                    cout << "LEFT " << hx << ":" << hy << endl;
                }
                if (dir == 'U') {
                    hy--;
                    cout << "UP   " << hx << ":" << hy << endl;
                }
                if (dir == 'D') {
                    hy++;
                    cout << "DOWN " << hx<<":"<< hy  << endl;
                }
                if (hx == tx) {  //same x, just need to maybe adjust y
                    if (hy - ty > 1) {
                        ty++;
                    }
                    else if (hy - ty < -1) {
                        ty--;
                    }
                }
                else if (hy == ty) {  //same y, just need to maybe adjust x
                    if (hx - tx > 1) {
                        tx++;
                    }
                    else if (hx - tx < -1) {
                        tx--;
                    }
                }
                else {  //diagonal case
                    if (abs(hx - tx) <= 1 && abs(hy - ty) <= 1) {
                        //do nothing
                    }
                    else {  //must update both x and y, can consider independently
                        if (hx > tx) {
                            tx++;
                        }
                        else {
                            tx--;
                        }
                        if (hy > ty) {
                            ty++;
                        }
                        else {
                            ty--;
                        }
                    }

                }
                cout << "TAIL " << tx << ":" << ty << endl;
                array[tx][ty] = 1;
            }

        }

        int count = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (array[i][j] > 0) {
                    count++;
                }
            }
        }

        cout << "P1: " << count << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //not for today

        return 0;
    }
};