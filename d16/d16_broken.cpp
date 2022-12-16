#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

//NOTE: Will this work?  Probably.  Will it be slow?  Definitely.
//Save for posterity, but probably need to do a graph of nodes and focus on travel times to new valves.

class d16 {
public:
    class Valve {
    public:
        string name;
        int rate;
        vector<string> connections;  //use string names or find pointers?
    };

    class Decision {
    public:
        int curRate;
        int timeLeft;
        int rel;
        string location;
        vector<string> openedValves;
    };

    int main_d() {
        ifstream f;
        f.open("d16/test2.txt");
        string line;
        string tmp;

        vector<Valve> valves;
        vector<Decision> decisions;
        int fnd = 0;
        int time = 30;
        int maxRelief = 0;

        while (getline(f, line)) {
            Valve v;

            line.erase(0, line.find(' ') + 1);  //erase to first space
            tmp = line.substr(0, line.find(' '));  //valve name
            v.name = tmp;

            line.erase(0, line.find('=') + 1);  //erase to =
            tmp = line.substr(0, line.find(';'));  //flow rate
            v.rate = stoi(tmp);

            line.erase(0, line.find("ves ") + 4);  //erase to beginning of connections list,
            //line now looks something like "CC, AA, EE" or "II"
            while (line.length() > 0) {
                fnd = line.find(',');
                if (fnd != string::npos) {
                    tmp = line.substr(0, fnd);
                    v.connections.push_back(tmp);
                    line.erase(0, line.find(", ") + 2);
                }
                else {
                    tmp = line;
                    v.connections.push_back(tmp);
                    line.erase(0, line.length());  //erase rest of line
                }

            }
            valves.push_back(v);

            if (v.name == "AA") {
                Decision d;
                d.curRate = 0;
                d.timeLeft = 30;
                d.rel = 0;
                d.location = "AA";
                decisions.push_back(d);
            }
        }

        while (decisions.size() > 0) {
            Decision d = decisions.front();
            decisions.erase(decisions.begin());
            d.rel = d.rel + d.curRate;  //increase released pressure
            d.timeLeft = d.timeLeft - 1;  //will always take time
            cout << "Evaluating decision of:" << decisions.size() << " - TimeLeft: " << d.timeLeft << endl;

            if (d.timeLeft == 0) {  //no time left, find if this is max
                if (d.rel > maxRelief) {
                    maxRelief = d.rel;
                }
            }
            else {  //if there's time left, consider next options
                bool valveOpen = false;  //determine if current valve is open
                for (string op : d.openedValves) {
                    if (op == d.location) {
                        valveOpen = true;
                    }
                }

                Valve curValve;  //get current valve data
                for (Valve v : valves) {
                    if (d.location == v.name) {
                        curValve = v;
                    }
                }
                if (curValve.rate == 0) {  //opening is a bad idea, let's just pretend
                    d.openedValves.push_back(curValve.name);
                }

                for (string next : curValve.connections) {  //add new locations to decision queue
                    d.location = next;
                    decisions.push_back(d);
                }

                if (!valveOpen && curValve.rate>0) {  //if valve is not open and opening will increase rate, add opening valve to decision queue
                    d.location = curValve.name;
                    d.openedValves.push_back(curValve.name);
                    d.curRate = d.curRate + curValve.rate;
                    decisions.push_back(d);
                }
            }
            
        }

        cout << "P1: " << maxRelief << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //maybe someday I'll get rid of that line.  Rereading files is for chumps.  Just store things



        return 0;
    }
};