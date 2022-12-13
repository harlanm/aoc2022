#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

class point {
public:
    int xpos;
    int ypos;
    int steps;
    point(int xp, int yp, int ste) {
        xpos = xp;
        ypos = yp;
        steps = ste;
    }
    point() {
        xpos = 0;
        ypos = 0;
        steps = 0;
    }
};

class d12 {
public:
    int main_d() {
        ifstream f;
        f.open("d12/test1.txt");
        string line;
        int num_lines = 41;//5
        int num_chars = 66;//8;
        int row = 0;
        int col = 0;
        vector<vector<char>> array(num_lines, vector<char>(num_chars, 0));
        vector<vector<char>> point_done(num_lines, vector<char>(num_chars, 0));
        queue<point> eval;
        int steps = 0;
        char curr = 0;
        int xdone = -1;
        int ydone = -1;
        point cp;

        while (getline(f, line)) {
            for (int i = 0; i < num_chars; i++) {
                curr = line[i];
                //if (curr == 'S') {  //Part 1
                if (curr == 'S' || curr == 'a') {  //Part 2
                    curr = 'a';
                    eval.push(point(i, row, 0));
                }
                if (curr == 'E') {
                    curr = 'z';
                    xdone = i;
                    ydone = row;
                }
                array[row][i] = curr;
            }
            row++;
        }

        bool done = false;
        while (!done) {
            cp = eval.front();
            eval.pop();
            cout << "Evaluating point " << cp.xpos << ":" << cp.ypos << endl;
            if (point_done[cp.ypos][cp.xpos] == 0) {
                if (cp.xpos == xdone && cp.ypos == ydone) {
                    done = true;
                    cout << "Found End in steps: " << cp.steps << endl;
                }
                if (cp.xpos > 0 && array[cp.ypos][cp.xpos] - array[cp.ypos][cp.xpos - 1] >= -1) {
                    eval.push(point(cp.xpos - 1, cp.ypos, cp.steps + 1));
                }
                if (cp.ypos > 0 && array[cp.ypos][cp.xpos] - array[cp.ypos - 1][cp.xpos] >= -1) {
                    eval.push(point(cp.xpos, cp.ypos - 1, cp.steps + 1));
                }
                if (cp.xpos < num_chars - 1 && array[cp.ypos][cp.xpos] - array[cp.ypos][cp.xpos + 1] >= -1) {
                    eval.push(point(cp.xpos + 1, cp.ypos, cp.steps + 1));
                }
                if (cp.ypos < num_lines - 1 && array[cp.ypos][cp.xpos] - array[cp.ypos + 1][cp.xpos] >= -1) {
                    eval.push(point(cp.xpos, cp.ypos + 1, cp.steps + 1));
                }
            }
            point_done[cp.ypos][cp.xpos] = 1;

        }

        int count = 0;
        cout << "P1: " << count << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //not for today

        //Not redoing part 2 today, just uncomment/comment lines 48/49

        return 0;
    }
};