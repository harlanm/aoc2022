#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class d8 {
public:
    int main_d() {
        ifstream f;
        f.open("d8/test1.txt");
        string line;
        int count = 0;
        int fline = 0;
        int fcol = 0;
        vector<vector<int>> trees(99);

        while (getline(f, line)) {
            fcol = 0;
            for (char c : line) {
                trees[fline].push_back(c - '0');
                fcol++;
            }
            fline++;
        }

        //fline,fcol are the size of the trees array
        bool counts = false;
        int rc = 0;
        bool rccounts = false;
        for (int i = 0; i < fline; i++) {
            for (int j = 0; j < fcol; j++) {
                counts = false; //start assuming tree does not count
                if (i == 0 || i == fline - 1 || j == 0 || j == fcol - 1) {
                    counts = true;
                }
                else {
                    rc = i-1;
                    rccounts = true;
                    while (rc >= 0) {
                        //cout << "COMPARING TREE: " << trees[i][j] << " TO: " << trees[rc][j] << endl;
                        if (trees[rc][j] >= trees[i][j]) {
                            rccounts = false;
                        }
                        rc--;
                    }
                    if (rccounts) {
                        counts = true;
                    }

                    rc = i+1;
                    rccounts = true;
                    while (rc < fline) {
                        if (trees[rc][j] >= trees[i][j]) {
                            rccounts = false;
                        }
                        rc++;
                    }
                    if (rccounts) {
                        counts = true;
                    }

                    rc = j-1;
                    rccounts = true;
                    while (rc >= 0) {
                        if (trees[i][rc] >= trees[i][j]) {
                            rccounts = false;
                        }
                        rc--;
                    }
                    if (rccounts) {
                        counts = true;
                    }

                    rc = j+1;
                    rccounts = true;
                    while (rc < fcol) {
                        if (trees[i][rc] >= trees[i][j]) {
                            rccounts = false;
                        }
                        rc++;
                    }
                    if (rccounts) {
                        counts = true;
                    }
                }

                if (counts) {
                    count++;
                }
            }
        }

        cout << "TREES P1: " << count << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //not for today
        int max = 0;
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;

        for (int i = 1; i < fline; i++) {
            for (int j = 1; j < fcol; j++){
                up = 0;
                down = 0;
                left = 0;
                right = 0;

                rc = i - 1;
                while (rc >= 0) {
                    up++;
                    if (trees[rc][j] >= trees[i][j]) {
                        rc = -1;
                    }
                    rc--;
                }

                rc = i + 1;
                while (rc < fline) {
                    down++;
                    if (trees[rc][j] >= trees[i][j]) {
                        rc = fline;
                    }
                    rc++;
                }

                rc = j - 1;
                while (rc >= 0) {
                    left++;
                    if (trees[i][rc] >= trees[i][j]) {
                        rc = -1;
                    }
                    rc--;
                }

                rc = j + 1;
                while (rc < fcol) {
                    right++;
                    if (trees[i][rc] >= trees[i][j]) {
                        rc = fcol;
                    }
                    rc++;
                }

                int score = up * down * left * right;
                if (score > max) {
                    max = score;
                }

            }
        }

        cout << "MAX SCORE P2: " << max << endl;

        return 0;
    }
};