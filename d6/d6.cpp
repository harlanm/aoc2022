#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class d6 {
public:
    int main_d() {
        ifstream f;
        f.open("d6/test1.txt");
        string line;
        vector<char> v;
        int count = 0;

        getline(f, line);
        v.push_back(line[count]);
        v.push_back(line[count+1]);
        v.push_back(line[count+2]);
        v.push_back(line[count+3]);  //get first 4 chars;
        count = 3;

        while (true) {
            if (v[count] != v[count - 1] && v[count] != v[count - 2] && v[count] != v[count - 3] &&
                v[count - 1] != v[count - 2] && v[count - 1] != v[count - 3] &&
                v[count - 2] != v[count - 3]) {
                break;
            }
            v.push_back(line[++count]);
            
        }


        cout << "P1: " << count << endl;  //think this might be off by 1 sometimes...
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //not the file, just reset the counts and such.  Probably use shorter names.
        vector<char> s;
        int p = 0;
        s.push_back(line[p]);
        s.push_back(line[p+1]);
        s.push_back(line[p+2]);
        s.push_back(line[p+3]);
        s.push_back(line[p+4]);
        s.push_back(line[p+5]);
        s.push_back(line[p+6]);
        s.push_back(line[p+7]);
        s.push_back(line[p+8]);
        s.push_back(line[p+9]);
        s.push_back(line[p+10]);
        s.push_back(line[p+11]);
        s.push_back(line[p+12]);
        s.push_back(line[p+13]);  //get first 14 chars
        p = 13;

        bool noMatch = true;
        while (noMatch) {
            noMatch = false;
            for (int i = 0; i < 14; i++) {
                for (int j = p - i-1; j > p - 14; j--) {
                    //cout << "comparing p:" << p << "i:" << i << "j:" << j << "char:" << s[p - i] << " char:" << s[j] << endl;
                    if (s[p - i] == s[j]) {
                        noMatch = true;
                    }
                }
            }
            s.push_back(line[++p]);
        }
        cout << "P2: " << p << endl;
        f.close();


        return 0;
    }
};