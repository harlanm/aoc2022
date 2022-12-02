#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class d2 {
public:
    int main_d2() {
        ifstream f;
        f.open("d2/test1.txt");
        int score = 0;
        int total_score = 0;
        int opponent = 0;  //Rock-A-1, Paper-B-2, Scissors-C-3
        int player = 0;  //Rock-X-1, Paper-Y-2, Scissors-Z-3
        int i = -1;  //need to track input file lines for debug...
        string line;
        while (getline(f, line)) {
            i++;
            score = 0;
            if (line[0] == 'A') {
                opponent = 1;
            }
            else if (line[0] == 'B') {
                opponent = 2;
            }
            else if (line[0] == 'C') {
                opponent = 3;
            }
            else {
                cout << "ERROR: UNKNOWN OPPONENT PLAY: " << line << " #" << i << endl;
            }
            if (line[2] == 'X') {
                player = 1;
                score += 1;
                if (opponent == 1) {
                    score += 3;
                }
                else if (opponent == 3) {
                    score += 6;
                }
            }
            else if (line[2] == 'Y') {
                player = 2;
                score += 2;
                if (opponent == 2) {
                    score += 3;
                }
                else if (opponent == 1) {
                    score += 6;
                }
            }
            else if (line[2] == 'Z') {
                player = 3;
                score += 3;
                if (opponent == 3) {
                    score += 3;
                }
                else if (opponent == 2) {
                    score += 6;
                }
            }
            else {
                cout << "ERROR: UNKNOWN PLAYER PLAY: " << line << " #" << i << endl;
            }
            total_score += score;
        }

        cout << "TOTAL SCORE: " << total_score << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        f.open("d2/test1.txt");
        score = 0;
        total_score = 0;
        opponent = 0;  //Rock-A-1, Paper-B-2, Scissors-C-3
        player = 0;  //Lose-X-1, Draw-Y-2, Win-Z-3
        i = -1;  //need to track input file lines for debug...
        while (getline(f, line)) {
            i++;
            score = 0;
            if (line[0] == 'A') {
                opponent = 1;
            }
            else if (line[0] == 'B') {
                opponent = 2;
            }
            else if (line[0] == 'C') {
                opponent = 3;
            }
            else {
                cout << "ERROR: UNKNOWN OPPONENT PLAY: " << line << " #" << i << endl;
            }
            if (line[2] == 'X') {  //lose
                player = 1;
                score += 0;  //0 for losing
                if (opponent == 1) {
                    score += 3; //scisors to lose to rock
                }
                else if (opponent == 2) {
                    score += 1; //rock to lose to paper
                }
                else if (opponent == 3) {
                    score += 2; //paper to lose to scissors
                }
            }
            else if (line[2] == 'Y') {  //draw
                player = 2;
                score += 3;  //3 for draw
                score += opponent; //draw, opponent's play is the right score to add.
            }
            else if (line[2] == 'Z') {  //win
                player = 3;
                score += 6;  //6 for win
                if (opponent == 1) {
                    score += 2; //paper to win to rock
                }
                else if (opponent == 2) {
                    score += 3; //scissors to win to paper
                }
                else if (opponent == 3) {
                    score += 1; //rock to win to scissors
                }
            }
            else {
                cout << "ERROR: UNKNOWN PLAYER PLAY: " << line << " #" << i << endl;
            }
            total_score += score;
        }

        cout << "TOTAL SCORE: " << total_score << endl;
        f.close();


        return 0;
    }
};