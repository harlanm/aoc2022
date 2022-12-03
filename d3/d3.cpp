#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class d3 {
public:
    int main_d() {
        ifstream f;
        f.open("d3/test1.txt");
        int score = 0;
        string line;
        int size = 0;
        int half = 0;
        char match = 0;
        while (getline(f, line)) {
            size = line.length();
            half = size / 2;
            match = 0;
            //cout << half << " " << size << endl;
            for (int i = 0; i < half; i++) {
                for (int j = 0; j < half; j++) {
                    if (line[i] == line[half + j]) {
                        match = line[i];
                    }
                }
            }
            if (match >= 'A' && match <= 'Z') {
                score += match - 'A' + 27;
            }
            else if (match >= 'a' && match <= 'z') {
                score += match - 'a' + 1;
            }
            else {
                cout << "ERROR!" << match << endl;
            }
        }

        cout << "TOTAL SCORE P1: " << score << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.
        f.open("d3/test1.txt");
        score = 0;
        string line1, line2, line3;
        int size1 = 0, size2 = 0, size3 = 0;
        match = 0;
        while (getline(f, line)) {
            if (size1 == 0) {
                line1 = line;
                size1 = line1.length();
            }
            else if (size2 == 0) {
                line2 = line;
                size2 = line2.length();
            }
            else if (size3 == 0) {
                line3 = line;
                size3 = line3.length();
            }
            else {
                cout << "ERROR assigining three lines" << endl;
            }
            if (size1 > 0 && size2 > 0 && size3 > 0) {
                match = 0;
                for (int i = 0; i < size1; i++) {
                    for (int j = 0; j < size2; j++) {
                        if (line1[i] == line2[j]) {
                            for (int k = 0; k < size3; k++) {
                                if (line1[i] == line3[k]) {
                                    match = line1[i];
                                }
                            }
                        }
                    }
                }

                //cout << "MATCH" << match << endl;
                if (match >= 'A' && match <= 'Z') {
                    score += match - 'A' + 27;
                }
                else if (match >= 'a' && match <= 'z') {
                    score += match - 'a' + 1;
                }
                else {
                    cout << "ERROR!" << match << endl;
                }
                size1 = 0;
                size2 = 0;
                size3 = 0;
            }

        }

        cout << "TOTAL SCORE P2: " << score << endl;
        f.close();



        return 0;
    }
};