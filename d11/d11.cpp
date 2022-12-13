#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <initializer_list>

using namespace std;

class Monkey {
public:

    int operation(int start, int monkey) {
        switch (monkey) {
        case 0:
            return start * 11;
        case 1:
            return start + 1;
        case 2:
            return start + 6;
        case 3:
            return start * start;
        case 4:
            return start * 7;
        case 5:
            return start + 8;
        case 6:
            return start + 5;
        case 7:
            return start + 7;
        default:
            cout << "ERROR in operation" << endl;
            return 0;
        }
    }
    long long operation(long long start, int monkey) {
        long long result;
        switch (monkey) {
        case 0:
            return start * 11;
        case 1:
            return start + 1;
        case 2:
            return start + 6;
        case 3:
            result = start * start;
            cout << result << endl;
            return result;  //pretty sure you can do this...return long long and it should fit...make sure to mod before and after
        case 4:
            return start * 7;
        case 5:
            return start + 8;
        case 6:
            return start + 5;
        case 7:
            return start + 7;
        default:
            cout << "ERROR in operation" << endl;
            return 0;
        }
    }

    int test(int worry, int monkey) {
        switch (monkey) {
        case 0:
            if (worry % 2 == 0) {
                return 7;
            }
            return 4;
        case 1:
            if (worry % 13 == 0) {
                return 3;
            }
            return 6;
            
        case 2:
            if (worry % 3 == 0) {
                return 1;
            }
            return 6;
            
        case 3:
            if (worry % 17 == 0) {
                return 7;
            }
            return 0;
            
        case 4:
            if (worry % 19 == 0) {
                return 5;
            }
            return 2;
            
        case 5:
            if (worry % 7 == 0) {
                return 2;
            }
            return 1;
            
        case 6:
            if (worry % 11 == 0) {
                return 3;
            }
            return 0;
            
        case 7:
            if (worry % 5 == 0) {
                return 4;
            }
            return 5;
            
        default:
            cout << "ERROR in operation" << endl;
            return 7;
        }
    }
    int test(long long worry, int monkey) {
        switch (monkey) {
        case 0:
            if (worry % 2 == 0) {
                return 7;
            }
            return 4;
        case 1:
            if (worry % 13 == 0) {
                return 3;
            }
            return 6;

        case 2:
            if (worry % 3 == 0) {
                return 1;
            }
            return 6;

        case 3:
            if (worry % 17 == 0) {
                return 7;
            }
            return 0;

        case 4:
            if (worry % 19 == 0) {
                return 5;
            }
            return 2;

        case 5:
            if (worry % 7 == 0) {
                return 2;
            }
            return 1;

        case 6:
            if (worry % 11 == 0) {
                return 3;
            }
            return 0;

        case 7:
            if (worry % 5 == 0) {
                return 4;
            }
            return 5;

        default:
            cout << "ERROR in operation" << endl;
            return 7;
        }
    }

};
class m0 :public Monkey {
    int operation(int start) {
        return start * 11;
    }
    int test(int worry) {
        if (worry % 2 == 0) {
            return 7;
        }
        return 4;
    }
};
class m1 :public Monkey {
    int operation(int start) {
        return start + 1;
    }
    int test(int worry) {
        if (worry % 13 == 0) {
            return 3;
        }
        return 6;
    }
};
class m2 :public Monkey {
    int operation(int start) {
        return start + 6;
    }
    int test(int worry) {
        if (worry % 3 == 0) {
            return 1;
        }
        return 6;
    }
};
class m3 :public Monkey {
    int operation(int start) {
        return start * start;
    }
    int test(int worry) {
        if (worry % 17 == 0) {
            return 7;
        }
        return 0;
    }
};
class m4 :public Monkey {
    int operation(int start) {
        return start * 7;
    }
    int test(int worry) {
        if (worry % 19 == 0) {
            return 5;
        }
        return 2;
    }
};
class m5 :public Monkey {
    int operation(int start) {
        return start + 8;
    }
    int test(int worry) {
        if (worry % 7 == 0) {
            return 2;
        }
        return 1;
    }
};
class m6 :public Monkey {
    int operation(int start) {
        return start + 5;
    }
    int test(int worry) {
        if (worry % 11 == 0) {
            return 3;
        }
        return 0;
    }
};
class m7 :public Monkey {
    int operation(int start) {
        return start + 7;
    }
    int test(int worry) {
        if (worry % 5 == 0) {
            return 4;
        }
        return 5;
    }
};

class d11 {
public:
    int main_d() {
        vector<Monkey> monkies;
        vector<vector<int>> items(8);
        int inspections[8] = { 0,0,0,0,0,0,0 };
        m0 mk0;
        for (int i : {89, 95, 92, 64, 87, 68}) {
            items[0].push_back(i);
        }
        m1 mk1;
        for (int i : {87, 67}) {
            items[1].push_back(i);
        }
        m2 mk2;
        for (int i : {95, 79, 92, 82, 60}) {
            items[2].push_back(i);
        }
        m3 mk3;
        for (int i : {67, 97, 56}) {
            items[3].push_back(i);
        }
        m4 mk4;
        for (int i : {80, 68, 87, 94, 61, 59, 50, 68}) {
            items[4].push_back(i);
        }
        m5 mk5;
        for (int i : {73, 51, 76, 59}) {
            items[5].push_back(i);
        }
        m6 mk6;
        for (int i : {92}) {
            items[6].push_back(i);
        }
        m7 mk7;
        for (int i : {99, 76, 78, 76, 79, 90, 89}) {
            items[7].push_back(i);
        }
        monkies.push_back(mk0);
        monkies.push_back(mk1);
        monkies.push_back(mk2);
        monkies.push_back(mk3);
        monkies.push_back(mk4);
        monkies.push_back(mk5);
        monkies.push_back(mk6);
        monkies.push_back(mk7);
        cout << "Don't worry be happy" << endl;

        int worry = 0;
        int result = 7;
        int item = 0;
        int size = 0;
        for (int day = 0; day < 20; day++) {
            cout << "Day " << day << endl;
            for (unsigned int m = 0; m < monkies.size(); m++) {
                size = items[m].size();
                cout << "Monkey " << m << endl;
                for(int i=0; i<size; i++){
                    item = items[m][i];
                    cout << "Inspecting item with initial worry: " <<item << endl;
                    //item = m.items[0];
                    inspections[m] = inspections[m] + 1;
                    worry = monkies[m].operation(item,m)/3;
                    result = monkies[m].test(worry,m);
                    items[result].push_back(worry);
                    //m.items.erase(m.items.begin());
                }
                items[m].erase(items[m].begin(), items[m].begin() + size);
            }

        }

        int m1 = 0;
        int m2 = 0;
        for (unsigned int m = 0; m < monkies.size(); m++) {
            cout << "Monkey inspections:" << inspections[m] << endl;
            if (inspections[m] > m1) {
                m2 = m1;
                m1 = inspections[m];
            }
            else if (inspections[m] > m2) {
                m2 = inspections[m];
            }
        }
        int resu = m1 * m2;
        cout << "P1:" << resu << endl;

        

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.

        //not for today
        //lol, who reads files when you can hardcode magic numbers :)
        vector<Monkey> monkies_p2;
        vector<vector<long long>> items_p2(8);
        int inspections_p2[8] = { 0,0,0,0,0,0,0 };
        //m0 mk0;
        for (int i : {89, 95, 92, 64, 87, 68}) {
            items_p2[0].push_back(i);
        }
        //m1 mk1;
        for (int i : {87, 67}) {
            items_p2[1].push_back(i);
        }
        //m2 mk2;
        for (int i : {95, 79, 92, 82, 60}) {
            items_p2[2].push_back(i);
        }
        //m3 mk3;
        for (int i : {67, 97, 56}) {
            items_p2[3].push_back(i);
        }
        //m4 mk4;
        for (int i : {80, 68, 87, 94, 61, 59, 50, 68}) {
            items_p2[4].push_back(i);
        }
        //m5 mk5;
        for (int i : {73, 51, 76, 59}) {
            items_p2[5].push_back(i);
        }
        //m6 mk6;
        for (int i : {92}) {
            items_p2[6].push_back(i);
        }
        //m7 mk7;
        for (int i : {99, 76, 78, 76, 79, 90, 89}) {
            items_p2[7].push_back(i);
        }
        monkies_p2.push_back(mk0);
        monkies_p2.push_back(mk1);
        monkies_p2.push_back(mk2);
        monkies_p2.push_back(mk3);
        monkies_p2.push_back(mk4);
        monkies_p2.push_back(mk5);
        monkies_p2.push_back(mk6);
        monkies_p2.push_back(mk7);
        cout << "Don't worry be happy, but more worried this time" << endl;

        long long worry_p2 = 0;
        result = 7;
        long long item_p2 = 0;
        size = 0;
        long long mod = 2*13*3*17*19*7*11*5; //you only need to keep an item number that is common amongst the modulo operators., inspired by @hyper-neutrino
        for (int day = 0; day < 10000; day++) {
            cout << "Day " << day << endl;
            for (unsigned int m = 0; m < monkies_p2.size(); m++) {
                size = items_p2[m].size();
                cout << "Monkey " << m << endl;
                for (int i = 0; i < size; i++) {
                    item_p2 = items_p2[m][i];
                    cout << "Inspecting item with initial worry: " << item_p2 << endl;
                    if (item_p2 < 0) {
                        //just cause an error;
                        m1 = monkies_p2[10].test(1, 1);
                    }
                    //item = m.items_p2[0];
                    inspections_p2[m] = inspections_p2[m] + 1;
                    worry_p2 = monkies_p2[m].operation(item_p2, m);  //use the mod var post-operatoin to keep worry manageable
                    cout << "New Worry:" << worry_p2 << endl;
                    worry_p2 = worry_p2 % mod;
                    result = monkies_p2[m].test(worry_p2, m);
                    items_p2[result].push_back(worry_p2);
                    //m.items_p2.erase(m.items_p2.begin());
                }
                items_p2[m].erase(items_p2[m].begin(), items_p2[m].begin() + size);
            }

        }

        m1 = 0;
        m2 = 0;
        for (unsigned int m = 0; m < monkies_p2.size(); m++) {
            cout << "Monkey inspections_p2:" << inspections_p2[m] << endl;
            if (inspections_p2[m] > m1) {
                m2 = m1;
                m1 = inspections_p2[m];
            }
            else if (inspections_p2[m] > m2) {
                m2 = inspections_p2[m];
            }
        }
        long long resu_p2 = m1 * m2;
        cout << "P1:" << resu_p2 << endl;

        return 0;
    }
};