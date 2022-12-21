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

class Monkey3 {
public:
    string name;
    char op;
    bool done;
    bool orig_done;
    long long result;
    string f1;
    string f2;

};

class d23 {
public:
    int main_d() {

        ifstream f;
        f.open("d21/test1.txt");
        string line;
        string tmp;
        long long v;

        Monkey3* mky = nullptr;
        map<string, Monkey3*> map;

        //zfcb: 2
        //bfpc: nzdw * vbbw
        while (getline(f, line)) {
            mky = new Monkey3();
            tmp = line.substr(0, line.find(':'));
            mky->name = tmp;
            line.erase(0, line.find(": ") + 2);
            if (line[0] >= '0' && line[0] <= '9') {
                v = stoll(line);
                mky->done = true;
                mky->orig_done = true;
                mky->result = v;
            }
            else {
                tmp = line.substr(0, line.find(' '));
                mky->f1 = tmp;
                line.erase(0, line.find(' ') + 1);
                mky->op = line[0];
                line.erase(0, 2);
                mky->f2 = line;
                mky->done = false;
                mky->orig_done = false;
            }
            map[mky->name] = mky;
        }

        while (map["root"]->done == false) {
            for (auto m : map) {
                mky = m.second;
                if (!mky->done) {
                    if (map[mky->f1]->done && map[mky->f2]->done) {
                        if (mky->op == '+') {
                            mky->result = map[mky->f1]->result + map[mky->f2]->result;
                        }
                        else if (mky->op == '-') {
                            mky->result = map[mky->f1]->result - map[mky->f2]->result;
                        }
                        else if (mky->op == '*') {
                            mky->result = map[mky->f1]->result * map[mky->f2]->result;
                        }
                        else if (mky->op == '/') {
                            mky->result = map[mky->f1]->result / map[mky->f2]->result;
                        }
                        else {
                            cout << "ERROR: Unknown op: " << mky->op << endl;
                        }
                        mky->done = true;
                    }
                }
            }

        }

        cout << "P1: Root says: " << map["root"]->result << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.
        //nope, not today
        //is it cheating to do a binary search based on runtime overflows?
        long long min = 0;
        long long max = 3342154812539;//667893105415394;//  8070450532247928830;//seems to break above this//LLONG_MAX;
        //also 3342154812540 definitely works but the site says it's too high...are we sure there's only 1 solution? (note, it has invalid int division)
        while (map[map["root"]->f1]->result != map[map["root"]->f2]->result) {
            cout << "does not match: " << map[map["root"]->f1]->result << " " << map[map["root"]->f2]->result << endl;
            //reset dones
            for (auto m : map) {
                mky = m.second;
                mky->done = mky->orig_done;
            }

            //increment human, use a binary search.  f2 is constant, f1 changes
            if (map[map["root"]->f1]->result > map[map["root"]->f2]->result && map[map["root"]->f1]->result > 0) {
                cout << "F1 > F2, should increase human" << endl;
                min = map["humn"]->result;
                if (max > LLONG_MAX - map["humn"]->result) {
                    map["humn"]->result = max / 2 + map["humn"]->result / 2;
                }
                else {
                    map["humn"]->result = (max + map["humn"]->result) / 2;
                }
            }
            else {
                cout << "F1 < F2, should decrease human ------------------------" << endl;
                max = map["humn"]->result;
                map["humn"]->result = (min + map["humn"]->result) / 2;
            }
            cout << "Trying with human: " << map["humn"]->result << endl;

            while (map["root"]->done == false) {
                for (auto m : map) {
                    mky = m.second;
                    if (!mky->done) {
                        if (map[mky->f1]->done && map[mky->f2]->done) {
                            if (mky->op == '+') {
                                mky->result = map[mky->f1]->result + map[mky->f2]->result;
                            }
                            else if (mky->op == '-') {
                                mky->result = map[mky->f1]->result - map[mky->f2]->result;
                            }
                            else if (mky->op == '*') {
                                mky->result = map[mky->f1]->result * map[mky->f2]->result;
                            }
                            else if (mky->op == '/') {
                                mky->result = map[mky->f1]->result / map[mky->f2]->result;
                                if (mky->result * map[mky->f2]->result != map[mky->f1]->result) {
                                    cout << "ERROR: Result uses invalid int div" << endl;
                                }
                            }
                            else {
                                cout << "ERROR: Unknown op: " << mky->op << endl;
                            }
                            if (mky->result < 0) {
                                cout << "ERROR: Monkey overflowed: " << mky->result << endl;
                            }
                            mky->done = true;
                        }
                    }
                }
            }
        }

        cout << "P1: Human says: " << map["humn"]->result << endl;
        f.close();
        

        return 0;
    }
};