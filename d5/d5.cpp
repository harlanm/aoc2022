#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

class d5 {
public:
    int main_d() {
        ifstream f;
        f.open("d5/test1.txt");
        string line;
        int doneInit = 0;
        stack<string> initLines;
        stack<char> stacks[9];
        string m, fr, t;
        int move, from, to;
        char temp;
        
        while (getline(f, line)) {
            if (!doneInit) {  //constuct the initial stacks
                if (line[1] == '1') { //done getting lines, pop from getLines and push to initial stacks
                    while (!initLines.empty()) {
                        line = initLines.top();
                        initLines.pop();
                        for(int i = 0; i < 9; i++) {
                            if (line[1 + i * 4] != ' ') {
                                stacks[i].push(line[1 + i * 4]);
                            }
                        }

                    }
                    getline(f, line);  //remove empty line
                    doneInit = 1;
                }
                else {
                    initLines.push(line);
                }
            }
            else { //do move operations                //line = move 7 from 3 to 9
                line.erase(0, line.find(' ') + 1);     //line = 7 from 3 to 9
                m = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);     //line = from 3 to 9
                line.erase(0, line.find(' ') + 1);     //line = 3 to 9
                fr = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);     //line = to 9
                line.erase(0, line.find(' ') + 1);     //line = 9
                t = line;
                move = stoi(m);
                from = stoi(fr)-1;  //0-index from and to
                to = stoi(t)-1;
                for (int i = 0; i < move; i++) {
                    temp = stacks[from].top();
                    stacks[from].pop();
                    stacks[to].push(temp);
                }
            }

        }

        string output = "";
        for (int i = 0; i < 9; i++) {
            output.push_back(stacks[i].top());
        }
        cout << "TOP OF STACKS P1: " << output << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.
        f.open("d5/test1.txt");
        doneInit = 0;
        stack<string> initLines2;
        stack<char> stacks2[9];
        stack<char> temp2;

        while (getline(f, line)) {
            if (!doneInit) {  //constuct the initial stacks
                if (line[1] == '1') { //done getting lines, pop from getLines and push to initial stacks
                    while (!initLines2.empty()) {
                        line = initLines2.top();
                        initLines2.pop();
                        for (int i = 0; i < 9; i++) {
                            if (line[1 + i * 4] != ' ') {
                                stacks2[i].push(line[1 + i * 4]);
                            }
                        }

                    }
                    getline(f, line);  //remove empty line
                    doneInit = 1;
                }
                else {
                    initLines2.push(line);
                }
            }
            else { //do move operations                //line = move 7 from 3 to 9
                line.erase(0, line.find(' ') + 1);     //line = 7 from 3 to 9
                m = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);     //line = from 3 to 9
                line.erase(0, line.find(' ') + 1);     //line = 3 to 9
                fr = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);     //line = to 9
                line.erase(0, line.find(' ') + 1);     //line = 9
                t = line;
                move = stoi(m);
                from = stoi(fr) - 1;  //0-index from and to
                to = stoi(t) - 1;
                for (int i = 0; i < move; i++) {
                    temp = stacks2[from].top();
                    stacks2[from].pop();
                    temp2.push(temp);
                }
                for (int i = 0; i < move; i++) {
                    temp = temp2.top();
                    temp2.pop();
                    stacks2[to].push(temp);
                }
            }

        }

        output = "";
        for (int i = 0; i < 9; i++) {
            output.push_back(stacks2[i].top());
        }
        cout << "TOP OF STACKS P2: " << output << endl;
        f.close();


        return 0;
    }
};