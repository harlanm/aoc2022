#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class d10 {
public:
    int main_d() {
        ifstream f;
        f.open("d9/test1.txt");
        string line;
        int size = 1000;
        int x[10] = { size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2 };
        int y[10] = { size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2,size / 2 };
        //int tx = size/2;
        //int ty = size/2;
        vector<vector<int>> array(size, vector<int>(size, 0));

        char dir;
        int num;

        while (getline(f, line)) {
            dir = line[0];
            line.erase(0, line.find(' ') + 1);
            num = stoi(line);
            for (int i = 0; i < num; i++) {
                for (int k = 0; k < 10; k++) {
                    if (k == 0) {
                        if (dir == 'R') {
                            x[0]++;
                            cout << "RIGHT " << x[k] << ":" << y[k] << endl;
                        }
                        if (dir == 'L') {
                            x[0]--;
                            cout << "LEFT " << x[k] << ":" << y[k] << endl;
                        }
                        if (dir == 'U') {
                            y[0]--;
                            cout << "UP   " << x[k] << ":" << y[k] << endl;
                        }
                        if (dir == 'D') {
                            y[0]++;
                            cout << "DOWN " << x[k] << ":" << y[k] << endl;
                        }
                    }
                    else {
                        if (x[k - 1] == x[k]) {  //same x, just need to maybe adjust y
                            if (y[k - 1] - y[k] > 1) {
                                y[k]++;
                            }
                            else if (y[k - 1] - y[k] < -1) {
                                y[k]--;
                            }
                        }
                        else if (y[k - 1] == y[k]) {  //same y, just need to maybe adjust x
                            if (x[k - 1] - x[k] > 1) {
                                x[k]++;
                            }
                            else if (x[k - 1] - x[k] < -1) {
                                x[k]--;
                            }
                        }
                        else {  //diagonal case
                            if (abs(x[k - 1] - x[k]) <= 1 && abs(y[k - 1] - y[k]) <= 1) {
                                //do nothing
                            }
                            else {  //must update both x and y, can consider independently
                                if (x[k - 1] > x[k]) {
                                    x[k]++;
                                }
                                else {
                                    x[k]--;
                                }
                                if (y[k - 1] > y[k]) {
                                    y[k]++;
                                }
                                else {
                                    y[k]--;
                                }
                            }

                        }
                        cout << "TAIL" << k << " " << x[k] << ":" << y[k] << endl;
                        if (k == 9) {
                            array[x[k]][y[k]] = 1;
                        }
                    }
                }
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