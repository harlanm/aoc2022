#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class d4 {
public:
    int main_d() {
        ifstream f;
        f.open("d4/test1.txt");
        int count = 0;
        string line;
        string e11, e12, e21, e22;
        int s1start, s1end, s2start, s2end;
        while (getline(f, line)) {                 //line = 2-4,6-8
            e11 = line.substr(0, line.find('-'));
            line.erase(0, line.find('-') + 1);     //line = 4,6-8
            e12 = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);     //line = 6-8
            e21 = line.substr(0, line.find('-'));
            line.erase(0, line.find('-') + 1);     //line = 8
            e22 = line;

            s1start = stoi(e11);
            s1end = stoi(e12);
            s2start = stoi(e21);
            s2end = stoi(e22);

            if (s1start <= s2start && s1end >= s2end) {
                count++;
            }
            else if (s2start <= s1start && s2end >= s1end) {
                count++;
            }
            
        }

        cout << "COUNT P1: " << count << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.
        f.open("d4/test1.txt");
        count = 0;
        while (getline(f, line)) {                 //line = 2-4,6-8
            e11 = line.substr(0, line.find('-'));
            line.erase(0, line.find('-') + 1);     //line = 4,6-8
            e12 = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);     //line = 6-8
            e21 = line.substr(0, line.find('-'));
            line.erase(0, line.find('-') + 1);     //line = 8
            e22 = line;

            s1start = stoi(e11);
            s1end = stoi(e12);
            s2start = stoi(e21);
            s2end = stoi(e22);

            if (
                (s1start >= s2start && s1start <= s2end)  //logic credit @tobstern
                || (s1end >= s2start && s1end <= s2end)
                || (s2start >= s1start && s2start <= s1end)
                || (s2end >= s1start && s2end <= s1end)
                ) {
                count++;
            }

            /*if (s1start <= s2start && s1end >= s2end) {
                count++;
            }
            else if (s2start <= s1start && s2end >= s1end) {
                count++;
            }
            else if (s1end <= s2start || s2end <= s1start || s2start <=s1end || s1start<=s2end) {
                count++;
            }*/
            //else if (s2start <= s1start && s2end >= s1end) {
            //    count++;
            //}

        }

        cout << "COUNT P2: " << count << endl;
        f.close();



        return 0;
    }
};