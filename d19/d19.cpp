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

class Blueprint {
public:
    int id;
    int oreRobotOreCost;
    int clayRobotOreCost;
    int obsidianRobotOreCost;
    int obsidianRobotClayCost;
    int geodeRobotOreCost;
    int geodeRobotObsidianCost;

    Blueprint(int i, int orROrC, int clROrC, int obROrC, int obRClC, int geROrC, int geRObC) {
        id = i;
        oreRobotOreCost = orROrC;
        clayRobotOreCost = clROrC;
        obsidianRobotOreCost = obROrC;
        obsidianRobotClayCost = obRClC;
        geodeRobotOreCost = geROrC;
        geodeRobotObsidianCost = geRObC;
    };
};

struct Option {
    int minutes;
    int ore;
    int clay;
    int obsidian;
    int geode;
    int oreRobots;
    int clayRobots;
    int obsidianRobots;
    int geodeRobots;
};

class d19 {
public:
    int main_d() {

        ifstream f;
        f.open("d19/test1.txt");
        string line;
        int minutes = 24;
        vector<Blueprint> blueprints;
        int quality = 0;
        int totalQuality = 0;
        int numBP = 0;

        int id = 0;
        int orROrC = 0;
        int clROrC = 0;
        int obROrC = 0;
        int obRClC = 0;
        int geROrC = 0;
        int geRObC = 0;
        string tmp;

        while (getline(f, line)) {
            line.erase(0, line.find(' ') + 1);
            tmp = line.substr(0, line.find(':'));
            id = stoi(tmp);

            line.erase(0, line.find("sts ") + 4);
            tmp = line.substr(0, line.find(' '));
            orROrC = stoi(tmp);

            line.erase(0, line.find("sts ") + 4);
            tmp = line.substr(0, line.find(' '));
            clROrC = stoi(tmp);

            line.erase(0, line.find("sts ") + 4);
            tmp = line.substr(0, line.find(' '));
            obROrC = stoi(tmp);

            line.erase(0, line.find("and ") + 4);
            tmp = line.substr(0, line.find(' '));
            obRClC = stoi(tmp);

            line.erase(0, line.find("sts ") + 4);
            tmp = line.substr(0, line.find(' '));
            geROrC = stoi(tmp);

            line.erase(0, line.find("and ") + 4);
            tmp = line.substr(0, line.find(' '));
            geRObC = stoi(tmp);

            Blueprint bp = Blueprint(id, orROrC, clROrC, obROrC, obRClC, geROrC, geRObC);
            blueprints.push_back(bp);
            numBP++;
        }

        for (int b = 0; b < numBP; b++) {
            queue<Option> options;
            options.push(Option{ minutes,0,0,0,0,1,0,0,0 });
            int maxGeode = 0;
            map<unsigned long long, int> DP;  //store the number of Geodes for each time/resource/robot combination, stop evaluating if a similar Option has less geodes.
            while(options.size() > 0) {
                Option o = options.front();
                options.pop();
                unsigned long long key = o.minutes*2^(6*8) + o.ore*2^(6*7) + o.clay*2^(6*6) + o.obsidian*2^(6*5) + o.geode*2^(6*4) + o.oreRobots*2^(6*3) + o.clayRobots*2^(6*2) + o.obsidianRobots*2^(6*1) + o.geodeRobots*2^(6*0);  //assume nothing will exceed twice the number of minutes (ie 24*2 for part 1), need 6 bits
                if (DP[key] > o.geode) {  //don't continue evaluating this path, another option has produced more geodes at this time/resource/robot combination
                    continue;
                }
                else {
                    if (o.geode > 0) {
                        DP[key] = o.geode;  //store number of geodes in dynamic programming map, if it's more than 0.
                    }
                }
                if (o.geode > maxGeode) {
                    maxGeode = o.geode;  //keep track of which option is making the most geodes
                }
                if (o.minutes <= 0) {  //not sure how it would be less than 0, but who knows
                    if (o.geode > maxGeode) {
                        maxGeode = o.geode;  //go ahead and double check maxGeode...probably not needed here anymore
                    }
                    continue;  //time is done, do not requeue
                }
                if ((o.geode + o.geodeRobots*o.minutes + (o.minutes-1)^2) < maxGeode) {
                    continue;  //cannot produce more geodes than max, don't continue this branch
                }
                //5 things we can do: make any of the 4 robots or wait for more resources
                //always create resources, after considering if you can/should make more robots
                if (o.ore >= blueprints[b].geodeRobotOreCost && o.obsidian >= blueprints[b].geodeRobotObsidianCost) {  //always consider making a geode robot
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].geodeRobotOreCost), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots - blueprints[b].geodeRobotObsidianCost), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots), (o.obsidianRobots), (o.geodeRobots + 1) });
                }
                if (o.ore >= blueprints[b].obsidianRobotOreCost && o.clay >= blueprints[b].obsidianRobotClayCost && o.obsidianRobots < blueprints[b].geodeRobotObsidianCost) {  //consider making an obsidian robot if you don't already make enough obsidian to produce every minute
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].obsidianRobotOreCost), (o.clay + o.clayRobots - blueprints[b].obsidianRobotClayCost), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots), (o.obsidianRobots + 1), (o.geodeRobots) });
                }
                if (o.ore >= blueprints[b].clayRobotOreCost && o.clayRobots < blueprints[b].obsidianRobotClayCost) {  //consider making a clay robot if you don't already make enough clay to produce every minute
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].clayRobotOreCost), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots + 1), (o.obsidianRobots), (o.geodeRobots) });
                }
                if (o.ore >= blueprints[b].oreRobotOreCost && o.oreRobots < max(max(blueprints[b].oreRobotOreCost, blueprints[b].clayRobotOreCost), max(blueprints[b].obsidianRobotOreCost, blueprints[b].geodeRobotOreCost))) {  //consider making a clay robot if you don't make enough ore to produce any robot every minute
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].oreRobotOreCost), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots + 1), (o.clayRobots), (o.obsidianRobots), (o.geodeRobots) });
                }
                if (((o.ore < blueprints[b].geodeRobotOreCost || o.obsidian < blueprints[b].geodeRobotObsidianCost) && o.oreRobots > 0 && o.obsidianRobots > 0) ||  //might want to wait for geode robot
                    ((o.ore < blueprints[b].obsidianRobotOreCost || o.clay < blueprints[b].obsidianRobotClayCost) && o.oreRobots > 0 && o.clayRobots > 0 && o.obsidianRobots < blueprints[b].geodeRobotObsidianCost) || //might want to wait for obsidian robot
                    ((o.ore < blueprints[b].clayRobotOreCost) && o.oreRobots > 0 && o.clayRobots < blueprints[b].obsidianRobotClayCost) || //might want to wait for clay robot
                    ((o.ore < blueprints[b].oreRobotOreCost) && o.oreRobots > 0 && o.oreRobots < max(max(blueprints[b].oreRobotOreCost, blueprints[b].clayRobotOreCost), max(blueprints[b].obsidianRobotOreCost, blueprints[b].geodeRobotOreCost))) // might want to wait for ore robot
                    ) {  //only wait for resources if there is already a robot that produces it.
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots), (o.obsidianRobots), (o.geodeRobots) });
                }
            }
            cout << "Max Geodes for Blueprint: " << blueprints[b].id << " is: " << maxGeode << endl;
            totalQuality = totalQuality + blueprints[b].id * maxGeode;
        }

        cout << "P1: Total Quality: " << totalQuality << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        int qualMult = 1;
        minutes = 32;

        for (int b = 0; (b < numBP) && (b<3); b++) {
            queue<Option> options;
            options.push(Option{ minutes,0,0,0,0,1,0,0,0 });
            int maxGeode = 0;
            map<unsigned long long, int> DP;  //store the number of Geodes for each time/resource/robot combination, stop evaluating if a similar Option has less geodes.
            while (options.size() > 0) {
                Option o = options.front();
                options.pop();
                unsigned long long key = o.minutes * 2 ^ (6 * 8) + o.ore * 2 ^ (6 * 7) + o.clay * 2 ^ (6 * 6) + o.obsidian * 2 ^ (6 * 5) + o.geode * 2 ^ (6 * 4) + o.oreRobots * 2 ^ (6 * 3) + o.clayRobots * 2 ^ (6 * 2) + o.obsidianRobots * 2 ^ (6 * 1) + o.geodeRobots * 2 ^ (6 * 0);  //assume nothing will exceed twice the number of minutes (ie 24*2 for part 1), need 6 bits
                if (DP[key] > o.geode) {  //don't continue evaluating this path, another option has produced more geodes at this time/resource/robot combination
                    continue;
                }
                else {
                    if (o.geode > 0) {
                        DP[key] = o.geode;  //store number of geodes in dynamic programming map, if it's more than 0.
                    }
                }
                if (o.geode > maxGeode) {
                    maxGeode = o.geode;  //keep track of which option is making the most geodes
                }
                if (o.minutes <= 0) {  //not sure how it would be less than 0, but who knows
                    if (o.geode > maxGeode) {
                        maxGeode = o.geode;  //go ahead and double check maxGeode...probably not needed here anymore
                    }
                    continue;  //time is done, do not requeue
                }
                if ((o.geode + o.geodeRobots * o.minutes + (o.minutes - 1) ^ 2) < maxGeode) {
                    continue;  //cannot produce more geodes than max, don't continue this branch
                }
                //5 things we can do: make any of the 4 robots or wait for more resources
                //always create resources, after considering if you can/should make more robots
                if (o.ore >= blueprints[b].geodeRobotOreCost && o.obsidian >= blueprints[b].geodeRobotObsidianCost) {  //always consider making a geode robot
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].geodeRobotOreCost), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots - blueprints[b].geodeRobotObsidianCost), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots), (o.obsidianRobots), (o.geodeRobots + 1) });
                }
                if (o.ore >= blueprints[b].obsidianRobotOreCost && o.clay >= blueprints[b].obsidianRobotClayCost && o.obsidianRobots < blueprints[b].geodeRobotObsidianCost) {  //consider making an obsidian robot if you don't already make enough obsidian to produce every minute
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].obsidianRobotOreCost), (o.clay + o.clayRobots - blueprints[b].obsidianRobotClayCost), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots), (o.obsidianRobots + 1), (o.geodeRobots) });
                }
                if (o.ore >= blueprints[b].clayRobotOreCost && o.clayRobots < blueprints[b].obsidianRobotClayCost) {  //consider making a clay robot if you don't already make enough clay to produce every minute
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].clayRobotOreCost), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots + 1), (o.obsidianRobots), (o.geodeRobots) });
                }
                if (o.ore >= blueprints[b].oreRobotOreCost && o.oreRobots < max(max(blueprints[b].oreRobotOreCost, blueprints[b].clayRobotOreCost), max(blueprints[b].obsidianRobotOreCost, blueprints[b].geodeRobotOreCost))) {  //consider making a clay robot if you don't make enough ore to produce any robot every minute
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots - blueprints[b].oreRobotOreCost), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots + 1), (o.clayRobots), (o.obsidianRobots), (o.geodeRobots) });
                }
                if (((o.ore < blueprints[b].geodeRobotOreCost || o.obsidian < blueprints[b].geodeRobotObsidianCost) && o.oreRobots > 0 && o.obsidianRobots > 0) ||  //might want to wait for geode robot
                    ((o.ore < blueprints[b].obsidianRobotOreCost || o.clay < blueprints[b].obsidianRobotClayCost) && o.oreRobots > 0 && o.clayRobots > 0 && o.obsidianRobots < blueprints[b].geodeRobotObsidianCost) || //might want to wait for obsidian robot
                    ((o.ore < blueprints[b].clayRobotOreCost) && o.oreRobots > 0 && o.clayRobots < blueprints[b].obsidianRobotClayCost) || //might want to wait for clay robot
                    ((o.ore < blueprints[b].oreRobotOreCost) && o.oreRobots > 0 && o.oreRobots < max(max(blueprints[b].oreRobotOreCost, blueprints[b].clayRobotOreCost), max(blueprints[b].obsidianRobotOreCost, blueprints[b].geodeRobotOreCost))) // might want to wait for ore robot
                    ) {  //only wait for resources if there is already a robot that produces it.
                    options.push(Option{ (o.minutes - 1), (o.ore + o.oreRobots), (o.clay + o.clayRobots), (o.obsidian + o.obsidianRobots), (o.geode + o.geodeRobots), (o.oreRobots), (o.clayRobots), (o.obsidianRobots), (o.geodeRobots) });
                }
            }
            cout << "Max Geodes for Blueprint: " << blueprints[b].id << " is: " << maxGeode << endl;
            qualMult = qualMult * maxGeode;
        }

        cout << "P2: Quality Multiple: " << qualMult << endl;
        f.close();

        return 0;
    }
};