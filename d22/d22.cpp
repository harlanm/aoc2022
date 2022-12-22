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

class d22 {
public:
    int main_d() {

        ifstream f;
        f.open("d22/test2.txt");
        int faceSize = 4;
        string line;
        string tmp;
        int row = 0;
        int col = 0;
        int dir = 0;  //dir is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)
        int numCols = 0;
        int numRows = 0;
        int lineSize = 0;
        vector<vector<int>> a;  //0 for empty space, 1 for open space, 2 for wall
        vector<vector<int>> face;  //0 for empty space, 1 for front, 2 for top, 3 for back, 4 for bottom, 5 for right side, 6 for left side
        unsigned int Rpos = 0;
        unsigned int Lpos = 0;
        int move = 0;
        bool startPlaced = false;
        int startRow = 0;
        int startCol = 0;
        string instructions;

        while (getline(f, line)) {
            lineSize = line.length();
            numCols = max(numCols, lineSize);
            if (lineSize < 5) {  //find end of map, next line will be instructions
                break;
            }
            a.push_back(vector<int>(numCols,0));
            face.push_back(vector<int>(numCols,0));
            for (int i = 0; i < lineSize; i++) {
                if (line[i] == '.') {
                    a[numRows][i] = 1;
                    if (!startPlaced) {
                        row = numRows;
                        col = i;
                        startRow = row;  //save for part 2
                        startCol = col;
                        startPlaced = true;
                    }
                }
                if (line[i] == '#') {
                    a[numRows][i] = 2;
                }
                //find face
                //0 for empty space, 1 for front, 2 for top, 3 for back, 4 for bottom, 5 for right side, 6 for left side
                if (line[1] != ' ') {
                    if (row >= startRow && col >= startCol && row < (startRow + faceSize) && col < (startCol + faceSize)) {
                        face[numRows][i] == 1; //front
                    }

                }
            }
            numRows++;
        }
        getline(f, line);  //line contains instructions
        instructions = line;  //save for part 2
        while (line.length() > 0) {
            //cout << line << endl;
            Rpos = line.find('R');
            Lpos = line.find('L');
            if (Rpos == string::npos) {
                Rpos = line.length() + 10;
            }
            if (Lpos == string::npos) {
                Lpos = line.length() + 10;
            }
            if (Rpos > line.length() && Lpos > line.length()) {
                move = stoi(line);
                line.erase(0, line.length());
            }
            else if (Rpos < Lpos) {
                tmp = line.substr(0, Rpos);
                move = stoi(tmp);
                line.erase(0, Rpos);  //not +1, leave the R
            }
            else if (Lpos < Rpos){
                tmp = line.substr(0, Lpos);
                move = stoi(tmp);
                line.erase(0, Lpos);  //not +1, leave the L
            }
            //move
            //dir is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)
            if (dir == 0) { //right
                //cout << "Moving " << move << " right" << endl;
                for (int i = 0; i < move; i++) {
                    if (col == a[row].size() - 1 || a[row][col + 1] == 0) {  //wrap to other side and check for wall
                        int j = 0;
                        while (a[row][j] == 0) {
                            j++;
                        }
                        if (a[row][j] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            col = j;
                        }
                    }
                    else if (a[row][col + 1] == 1) {  //open space
                        col++;
                    }
                    else if (a[row][col + 1] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else if (dir == 1) {  //down
                //cout << "Moving " << move << " down" << endl;
                for (int i = 0; i < move; i++) {
                    if (row == numRows - 1 || a[row + 1][col] == 0) {  //wrap to other side and check for wall
                        int j = 0;
                        while (a[j][col] == 0) {
                            j++;
                        }
                        if (a[j][col] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            row = j;
                        }
                    }
                    else if (a[row + 1][col] == 1) {  //open space
                        row++;
                    }
                    else if (a[row + 1][col] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else if (dir == 2) {  //left
                //cout << "Moving " << move << " left" << endl;
                for (int i = 0; i < move; i++) {
                    if (col == 0 || a[row][col - 1] == 0) {  //wrap to other side and check for wall
                        int j = a[row].size() - 1;
                        while (a[row][j] == 0) {
                            j--;
                        }
                        if (a[row][j] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            col = j;
                        }
                    }
                    else if (a[row][col - 1] == 1) {  //open space
                        col--;
                    }
                    else if (a[row][col - 1] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else if (dir == 3) {  //up
                //cout << "Moving " << move << " up" << endl;
                for (int i = 0; i < move; i++) {
                    if (row == 0 || a[row - 1][col] == 0) {  //wrap to other side and check for wall
                        int j = numRows - 1;
                        while (a[j][col] == 0) {
                            j--;
                        }
                        if (a[j][col] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            row = j;
                        }
                    }
                    else if (a[row - 1][col] == 1) {  //open space
                        row--;
                    }
                    else if (a[row - 1][col] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else {
                cout << "ERROR: Unknown dir: " << dir << endl;
            }
            //cout << "Moved to: col: " << col << " row: " << row << endl;

            //change direction if there is a direction
            //dir is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)
            if (line.length() > 0) {
                if (line[0] == 'R') {
                    dir = (dir + 1) % 4;
                }
                else {  //L
                    dir = (dir + 3) % 4;
                }
                line.erase(0, 1);
            }

            //cout << "direction is: " << dir << endl;
        }

        cout << "P1: " << 1000 * (row+1) + 4 * (col+1) + dir << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //don't need to reread file, just restore some vals
        //also add face awareness when parsing map
        line = instructions;
        row = startRow;
        col = startCol;
        dir = 0;

        while (line.length() > 0) {
            cout << line << endl;
            Rpos = line.find('R');
            Lpos = line.find('L');
            if (Rpos == string::npos) {
                Rpos = line.length() + 10;
            }
            if (Lpos == string::npos) {
                Lpos = line.length() + 10;
            }
            if (Rpos > line.length() && Lpos > line.length()) {
                move = stoi(line);
                line.erase(0, line.length());
            }
            else if (Rpos < Lpos) {// && Rpos != string::npos) {
                tmp = line.substr(0, Rpos);
                move = stoi(tmp);
                line.erase(0, Rpos);  //not +1, leave the R
            }
            else if (Lpos < Rpos) {// && Lpos != string::npos) {
                tmp = line.substr(0, Lpos);
                move = stoi(tmp);
                line.erase(0, Lpos);  //not +1, leave the L
            }
            //move
            move:  //label for move, gonna use goto's :)
            //dir is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)
            if (dir == 0) { //right
                cout << "Moving " << move << " right" << endl;
                for (int i = 0; i < move; i++) {
                    if (col == a[row].size() - 1 || a[row][col + 1] == 0) {  //wrap to other side and check for wall
                        int j = 0;
                        while (a[row][j] == 0) {
                            j++;
                        }
                        if (a[row][j] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            col = j;
                        }
                    }
                    else if (a[row][col + 1] == 1) {  //open space
                        col++;
                    }
                    else if (a[row][col + 1] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else if (dir == 1) {  //down
                cout << "Moving " << move << " down" << endl;
                for (int i = 0; i < move; i++) {
                    if (row == numRows - 1 || a[row + 1][col] == 0) {  //wrap to other side and check for wall
                        int j = 0;
                        while (a[j][col] == 0) {
                            j++;
                        }
                        if (a[j][col] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            row = j;
                        }
                    }
                    else if (a[row + 1][col] == 1) {  //open space
                        row++;
                    }
                    else if (a[row + 1][col] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else if (dir == 2) {  //left
                cout << "Moving " << move << " left" << endl;
                for (int i = 0; i < move; i++) {
                    if (col == 0 || a[row][col - 1] == 0) {  //wrap to other side and check for wall
                        int j = a[row].size() - 1;
                        while (a[row][j] == 0) {
                            j--;
                        }
                        if (a[row][j] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            col = j;
                        }
                    }
                    else if (a[row][col - 1] == 1) {  //open space
                        col--;
                    }
                    else if (a[row][col - 1] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else if (dir == 3) {  //up
                cout << "Moving " << move << " up" << endl;
                for (int i = 0; i < move; i++) {
                    if (row == 0 || a[row - 1][col] == 0) {  //wrap to other side and check for wall
                        int j = numRows - 1;
                        while (a[j][col] == 0) {
                            j--;
                        }
                        if (a[j][col] == 2) {  //wall, stop moving
                            break;
                        }
                        else {  //move to open space on other side
                            row = j;
                        }
                    }
                    else if (a[row - 1][col] == 1) {  //open space
                        row--;
                    }
                    else if (a[row - 1][col] == 2) {  //wall, stop moving
                        break;
                    }
                }
            }
            else {
                cout << "ERROR: Unknown dir: " << dir << endl;
            }
            cout << "Moved to: col: " << col << " row: " << row << endl;

            //change direction if there is a direction
            //dir is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)
            if (line.length() > 0) {
                if (line[0] == 'R') {
                    dir = (dir + 1) % 4;
                }
                else {  //L
                    dir = (dir + 3) % 4;
                }
                line.erase(0, 1);
            }

            cout << "direction is: " << dir << endl;
        }

        cout << "P2: " << 1000 * (row + 1) + 4 * (col + 1) + dir << endl;

        return 0;
    }
};