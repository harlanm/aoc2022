#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
using namespace std;


class d14 {
public:
    int main_d() {
        ifstream f;
        f.open("d14/test1.txt");
        string line;
        int height = 200;//5
        int width = 1000;//8;
        int row = 0;
        int col = 0;
        vector<vector<char>> array(height, vector<char>(width, 0));  //1 for rock, 2 for sand, 0 for empty

        int xstart = 0;
        int ystart = 0;
        int xend = 0;
        int yend = 0;
        string tmp;
        int fnd = 0;
        bool done = false;
        int ymax = 0;

        while (getline(f, line)) {
            tmp = line.substr(0, line.find(','));
            xstart = stoi(tmp);
            line.erase(0, line.find(',') + 1);
            tmp = line.substr(0, line.find(' '));
            ystart = stoi(tmp);
            line.erase(0, line.find(' ') + 1);
            if (ystart > ymax) {
                ymax = ystart;
            }
            while (line.length() > 0) {
                line.erase(0, 3);  //remove leading "-> " (3 chars)
                tmp = line.substr(0, line.find(','));
                xend = stoi(tmp);
                line.erase(0, line.find(',') + 1);
                fnd = line.find(' ');
                if(fnd != string::npos){  //if there's no space after the yend number, we've reached the end of the line
                    tmp = line.substr(0, line.find(' '));
                    yend = stoi(tmp);
                    line.erase(0, line.find(' ') + 1);
                }
                else {
                    tmp = line;
                    yend = stoi(tmp);
                    line.erase(0, line.length());
                }

                if (xstart == xend) {
                    array[ystart][xstart] = 1;
                }
                else if (xstart > xend) {
                    for (int i = xend; i <= xstart; i++) {
                        array[ystart][i] = 1;
                    }
                }
                else if (xend > xstart) {
                    for (int i = xstart; i <= xend; i++) {
                        array[ystart][i] = 1;
                    }
                }

                if (ystart == yend) {
                    array[ystart][xstart] = 1;
                }
                else if (ystart > yend) {
                    for (int i = yend; i <= ystart; i++) {
                        array[i][xstart] = 1;
                    }
                }
                else if (yend > ystart) {
                    for (int i = ystart; i <= yend; i++) {
                        array[i][xstart] = 1;
                    }
                }
                if (yend > ymax) {
                    ymax = yend;
                }

                xstart = xend;
                ystart = yend;

            }

        }
        cout << "YMAX:" << ymax << endl;
        for (int i = 0; i < width; i++) {
            array[ymax + 2][i] = 1;  //add rock floor 2 below for part 2
        }

        done = false;
        int count = 1;  //start with first sand
        int xpos = 500;
        int ypos = 0;
        while (!done) {
            if (ypos == ymax+1) {  //below max, found the limit
                done = true;
            }
            else if (array[ypos + 1][xpos] == 0) {
                ypos = ypos + 1;
            }
            else if (array[ypos+1][xpos-1] == 0) {
                xpos = xpos - 1;
                ypos = ypos + 1;
            }
            else if (array[ypos + 1][xpos + 1] == 0) {
                xpos = xpos + 1;
                ypos = ypos + 1;
            }
            else {
                array[ypos][xpos] = 2;  //place sand here
                count = count + 1;
                xpos = 500;
                ypos = 0;
            }

        }

        count = count - 1;  //last sand will not rest

        cout << "P1: " << count << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //just keep going from previous input!
        done = false;
        count++;  //prep next sand
        xpos = 500;
        ypos = 0;
        while (!done) {
            if (array[0][500] != 0) {  //starting point is filled, done with sand
                done = true;
                count--;  //get rid of the "next" sand from count
            }
            else if (array[ypos + 1][xpos] == 0) {
                ypos = ypos + 1;
            }
            else if (array[ypos + 1][xpos - 1] == 0) {
                xpos = xpos - 1;
                ypos = ypos + 1;
            }
            else if (array[ypos + 1][xpos + 1] == 0) {
                xpos = xpos + 1;
                ypos = ypos + 1;
            }
            else {
                array[ypos][xpos] = 2;  //place sand here
                count = count + 1;
                xpos = 500;
                ypos = 0;
            }

        }

        cout << "P2: " << count << endl;
        f.close();


        return 0;
    }
};