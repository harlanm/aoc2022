#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
using namespace std;


class d15 {
public:

    class SensorBeaconPair {
    public:

        int sensorRow;
        int sensorCol;
        int beconRow;
        int beconCol;
        int mDist;

        int calmDist() {
            return abs(sensorCol - beconCol) + abs(sensorRow - beconRow);
        }

    };

    int main_d() {
        ifstream f;
        f.open("d15/test1.txt");
        string line;
        string tmp;

        vector<SensorBeaconPair> pairs;
        int row = 2000000; // 10;
        int minCol = -3909820; //-5;
        int maxCol = 49372790; //25;
        bool found = false;
        int dist = 0;

        while (getline(f, line)) {
            SensorBeaconPair sbp;

            line.erase(0, line.find('=') + 1);  //erase to first x=
            tmp = line.substr(0, line.find(','));  //sensor x/col
            sbp.sensorCol = stoi(tmp);

            line.erase(0, line.find('=') + 1);  //erase to next y=
            tmp = line.substr(0, line.find(':'));  //sensor y/row
            sbp.sensorRow = stoi(tmp);

            line.erase(0, line.find('=') + 1);  //erase to next x=
            tmp = line.substr(0, line.find(','));  //becon x/col
            sbp.beconCol = stoi(tmp);

            line.erase(0, line.find('=') + 1);  //erase to next y=
            tmp = line;                     //becon y/row is just the rest of line
            sbp.beconRow = stoi(tmp);

            sbp.mDist = sbp.calmDist();  //calculate distance

            pairs.push_back(sbp);
        }
        
        int count = 0;
        for (int c = minCol; c<=maxCol; c++) {
            int r = row;
            for (SensorBeaconPair sbp : pairs) {
                dist = abs(sbp.sensorCol - c) + abs(sbp.sensorRow - r);
                if (dist <= sbp.mDist) {
                    // check if there is a sensor or beacon there
                    found = false;
                    for (SensorBeaconPair sb : pairs) {
                        if (sb.beconCol == c && sb.beconRow == r) { 
                            found = true;
                        }
                        if (sb.sensorCol == c && sb.sensorRow == r) { 
                            found = true;
                        }
                    }
                    if (!found) {
                        count++;
                    }
                    break;
                }
            }
        }

        cout << "P1: " << count << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //maybe someday I'll get rid of that line.  Rereading files is for chumps.  Just store things
        minCol = 0;
        maxCol = 4000000; //20;
        int minRow = minCol;
        int maxRow = maxCol;
        bool possibleLocation = true;

        //Brute force through ~4000000^2 positions?  Seems like a good idea to me...
        for (int c = minCol; c <= maxCol; c++) {
            for (int r = minRow; r <= maxRow; r++) {

                // check if there is a sensor or beacon there
                found = false;
                for (SensorBeaconPair sb : pairs) {
                    if (sb.beconCol == c && sb.beconRow == r) { 
                        found = true;
                    }
                    if (sb.sensorCol == c && sb.sensorRow == r) { 
                        found = true; 
                    }
                }
                if (!found) {
                    possibleLocation = true;
                    for (SensorBeaconPair sbp : pairs) {
                        dist = abs(sbp.sensorCol - c) + abs(sbp.sensorRow - r);
                        if (dist <= sbp.mDist) {
                            possibleLocation = false;
                            // To speed up, we can jump over some rows   
                            r = sbp.sensorRow + sbp.mDist - abs(sbp.sensorCol - c);
                            break;
                        }
                    }
                    if (possibleLocation && c > 0) {
                        long long freq = 4000000 * (long long)c + (long long)r;
                        cout << "P2: " << freq << endl;
                    }
                }

            }
        }



        return 0;
    }
};