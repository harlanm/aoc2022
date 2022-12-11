#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;


class Thing {
public:
    string name;
    int size;
    vector<Thing> children;

    Thing() {
        size = 0;
        name = "";
    }
    Thing(string n) {
        size = 0;
        name = n;
    }
    Thing(string n, int s) {
        size = s;
        name = n;
    }

    void addChild(Thing** t) {
        children.push_back(**t);
    }

    int getSize() {
        int s = size;
        for (auto child : children) {
            s += child.getSize();
        }
        return s;
    }


};

class d7 {
public:
    int main_d() {
        ifstream f;
        f.open("d7/test2.txt");
        string line;
        int count = 0;
        string cmd;
        string name;
        string size_s;
        int size;
        stack<Thing> dirs;
        Thing tmp;
        Thing file;

        while (getline(f, line)) {
            if (line[0] == '$') {  //do a command
                if (line[2] == 'c' && line[3] == 'd') {  //cd command
                    if (line[5] == '.' && line[6] == '.') {  //cd .., get current dir from top of stack
                        tmp = dirs.top();
                        dirs.pop();
                    }
                    else {  //push current dir to stack, make new dir, add it as child of 'current' dir (now on stack)
                        dirs.push(tmp);
                        line.erase(0, 5);
                        tmp = Thing(line);
                        Thing* thingptr = &tmp;
                        dirs.top().addChild(&thingptr);
                        cout << "ADDED DIR: " << tmp.name <<" TO DIR: " << dirs.top().name << endl;
                        cout << "has size" << dirs.top().children.size() << endl;
                    }
                }
                else if (line[2] == 'l' && line[3] == 's') {  //ls command
                    //don't really need to do anything with this line directly.
                }
                else {
                    cout << "ERROR with command: " << line << endl;
                }
            }
            else {  //output from ls
                if (line[0] == 'd' && line[1] == 'i' && line[2] == 'r') {
                    //don't do anything with dirs here
                }
                else {//make a file
                    size_s = line.substr(0, line.find(' '));
                    size = stoi(size_s);
                    line.erase(0, line.find(' ') + 1);
                    name = line;
                    file = Thing(name, size);
                    Thing* fileptr = &tmp;
                    tmp.addChild(&fileptr);
                    cout << "ADDED FILE: " << file.name <<" TO DIR: " <<tmp.name<< endl;
                    cout << "has size" << tmp.children.size() << endl;
                }

            }
        }

        while (dirs.size() > 2) {
            dirs.pop();  //get back to just / on dirs stack (and also a null obj...)
        }

        vector<Thing> v;
        v.push_back(dirs.top());

        int runningSize = 0;
        size = 0;
        while (v.size() > 0) {
            tmp = v.front();
            for (Thing d : tmp.children) {
                cout << "THING " << d.name << " has size:" << d.size << endl;
                if (d.size == 0) {
                    v.push_back(d);
                }
            }
            size = tmp.getSize();
            cout << "DIR: " << tmp.name << " SIZE: " << size << endl;
            if (size <= 100000) {
                runningSize += size;
            }
            v.erase(v.begin());
        }


        cout << "P1: " << runningSize << endl;  //think this might be off by 1 sometimes...
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.


        return 0;
    }
};