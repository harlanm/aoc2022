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

class d16 {
public:
    vector<ll> valveRelief;  //amount of pressure that will be released per minute by opening a valve
    vector<vector<ll>> valveTunnels;  //which valves are connected to a given valve

    ll best = 0;
    vector<ll> DP;  //DP=Dynamic Programming, essentially you only need to find the answer for each myPos/openedValves/time combination once, and can store it in here.

    //basically put all the interesting bits in this recursive function.  Calculates the score given a set of starting parameters
    //myPos and openedValves are used to index into a vector of valves that will release stored pressue values.
    ll scoreFromState(ll myPos, ll openedValves, ll time, ll other_players) {
        if (time == 0) {
            return other_players > 0 ? scoreFromState(0, openedValves, 26, other_players - 1) : 0LL;
        }

        ll key = openedValves * valveRelief.size() * 31 * 2 + myPos * 31 * 2 + time * 2 + other_players;
        if (DP[(unsigned int)key] >= 0) {
            return DP[(unsigned int)key];
        }

        ll ans = 0;
        bool myPosValveClosed = ((openedValves & (1LL << myPos)) == 0);  //check if valve at myPos is opened
        if (myPosValveClosed && valveRelief[(unsigned int)myPos] > 0) {  //only open a valve if it is not already opened and it will decrease pressure
            ll newOpenedValves = openedValves | (1LL << myPos);
            assert(newOpenedValves > openedValves);
            ans = max(ans, (time - 1) * valveRelief[(unsigned int)myPos] + scoreFromState(myPos, newOpenedValves, time - 1, other_players));
        }
        for (auto& y : valveTunnels[(unsigned int)myPos]) {  //recursively call for all connected valves
            ans = max(ans, scoreFromState(y, openedValves, time - 1, other_players));
        }
        DP[(unsigned int)key] = ans;
        return ans;
    }
    

    int main_d() {
        ifstream fin;
        fin.open("d16/test1.txt");
        map<string, pair<ll, vector<string>>> INPUT;
        while (!fin.eof()) {
            string S;
            getline(fin, S);
            std::istringstream iss(S);
            std::string word;

            ll idx = 0;
            string id;
            ll rate = 0;
            vector<string> NBR;
            while (std::getline(iss, word, ' ')) {
                if (idx == 1) {
                    id = word;
                }
                else if (idx == 4) {
                    rate = stoll(word.substr(5, word.size() - 6));
                }
                else if (idx >= 9) {
                    if (word[word.size() - 1] == ',') {
                        word = word.substr(0, word.size() - 1);
                    }
                    NBR.push_back(word);
                }
                idx++;
            }
            INPUT[id] = make_pair(rate, NBR);
        }

        int n = INPUT.size();
        map<string, int> INDEX_OF;
        vector<string> ORDER;
        ll nonzero = 0;
        // Convenient to have the start position have index 0
        for (auto& p : INPUT) {
            if (p.first == "AA") {
                INDEX_OF[p.first] = ORDER.size();
                ORDER.push_back(p.first);
                nonzero++;
            }
        }
        // put valves with non-zero flow rate first
        for (auto& p : INPUT) {
            if (p.second.first > 0) {
                INDEX_OF[p.first] = ORDER.size();
                ORDER.push_back(p.first);
                nonzero++;
            }
        }
        for (auto& p : INPUT) {
            if (INDEX_OF.count(p.first) == 0) {
                INDEX_OF[p.first] = ORDER.size();
                ORDER.push_back(p.first);
            }
        }

        valveRelief = vector<ll>(n, 0);
        for (int i = 0; i < n; i++) {
            valveRelief[i] = INPUT[ORDER[i]].first;
        }
        valveTunnels = vector<vector<ll>>(n, vector<ll>{});
        for (int i = 0; i < n; i++) {
            for (auto& y : INPUT[ORDER[i]].second) {
                valveTunnels[i].push_back(INDEX_OF[y]);
            }
        }

        DP = vector<ll>((1LL << nonzero) * n * 31 * 2, -1);
        //cerr << "DP size=" << DP.size() << endl;
        ll p1 = scoreFromState(0, 0, 30, 0);  //start at AA, you have 30 minutes, and it's just you
        cout << "P1: " << p1 << endl;

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //maybe someday I'll get rid of that line.  Rereading files is for chumps.  Just store things
        //especially with dynamic programming, since all of the calculated states from P1 can be reused without recalculating!

        ll p2 = scoreFromState(0, 0, 26, 1);  //start at AA, you have 26 minutes, and you have an elephant helper
        cout << "P2: " << p2 << endl;



        return 0;
    }
};