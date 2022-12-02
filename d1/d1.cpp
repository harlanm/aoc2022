#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    std::cout << "Hello World!" << endl;
    ifstream f;
    f.open("d1/test1.txt");
    int food = 0;
    int max = 0;
    int sum = 0;
    int m2=0, m3 = 0;  //Part 2
    string line;
    while (getline(f, line)) {
        if (line.length() > 1) {
            food = stoi(line);
            sum += food;
        }
        else {
            if (sum > max) {
                m3 = m2;  //part 2
                m2 = max; //part 2
                max = sum;
            }
            else if (sum > m2) { //part 2
                m3 = m2;
                m2 = sum;
            }
            else if (sum > m3) { //part 2
                m3 = sum;
            }
            sum = 0;
        }
    }

    cout << "MAX CALORIES:" << max << endl;

    //********************************Part 2****************************
    sum = max + m2 + m3;
    cout << "TOP 3 Calories:" << sum << endl;



    return 0;
}