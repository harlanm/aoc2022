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

class Node {
public:
    long long val;
    Node* next_orig;
    Node* next_sorted;
    Node* prev_sorted;

    Node(long long v, Node* no, Node* ns, Node* ps) {
        val = v;
        next_orig = no;
        next_sorted = ns;
        prev_sorted = ps;
    }

};

class d20 {
public:
    int main_d() {

        ifstream f;
        f.open("d20/test1.txt");
        string line;

        long long numNodes = 0;
        Node* tmp = nullptr;
        long long v;
        Node* prev = nullptr;
        Node* head = nullptr;
        Node* tmp2 = nullptr;
        Node* zero = nullptr;

        while (getline(f, line)) {
            v = stoll(line);
            if (numNodes == 0) {
                tmp = new Node(v, nullptr, nullptr, nullptr);
                head = tmp;
            }
            else {
                tmp = new Node(v, nullptr, nullptr, prev);
                prev->next_orig = tmp;
                prev->next_sorted = tmp;
            }
            if (v == 0) {
                zero = tmp;
            }
            prev = tmp;
            numNodes++;
        }

        //make circular
        tmp->next_orig = head;
        tmp->next_sorted = head;
        head->prev_sorted = tmp;

        tmp = head;
        for (int i = 0; i < numNodes; i++) {
            long long numSteps = tmp->val;
            if (numSteps >= 0) {
                for (int j = 0; j < numSteps; j++) {
                    tmp2 = tmp->next_sorted;
                    tmp->prev_sorted->next_sorted = tmp2;
                    tmp2->next_sorted->prev_sorted = tmp;
                    tmp2->prev_sorted = tmp->prev_sorted;
                    tmp->next_sorted = tmp2->next_sorted;
                    tmp->prev_sorted = tmp2;
                    tmp2->next_sorted = tmp;
                }
            }
            else {
                numSteps = numSteps * -1;
                for (int j = 0; j < numSteps; j++) {
                    tmp2 = tmp->prev_sorted;
                    tmp->next_sorted->prev_sorted = tmp2;
                    tmp2->prev_sorted->next_sorted = tmp;
                    tmp2->next_sorted = tmp->next_sorted;
                    tmp->prev_sorted = tmp2->prev_sorted;
                    tmp->next_sorted = tmp2;
                    tmp2->prev_sorted = tmp;
                }
            }
            tmp = tmp->next_orig;
        }

        long long coord = 0;
        tmp = zero;
        for (int i = 0; i < 1000; i++) {
            tmp = tmp->next_sorted;
        }
        cout << "NUM: " << tmp->val << endl;
        coord += tmp->val;
        for (int i = 0; i < 1000; i++) {
            tmp = tmp->next_sorted;
        }
        cout << "NUM: " << tmp->val << endl;
        coord += tmp->val;
        for (int i = 0; i < 1000; i++) {
            tmp = tmp->next_sorted;
        }
        cout << "NUM: " << tmp->val << endl;
        coord += tmp->val;
        cout << "P1: Coordinate: " << coord << endl;
        f.close();

        //*************************** Part 2 ****************************//
        //probably easier to just reread the file to maintain both answers.
        //hey, probably actually do that this time!

        f.open("d20/test1.txt");
        numNodes = 0;

        tmp = nullptr;
        prev = nullptr;
        head = nullptr;
        tmp2 = nullptr;
        zero = nullptr;
        long long dk = 811589153;

        while (getline(f, line)) {
            v = stoll(line) * dk;
            if (numNodes == 0) {
                tmp = new Node(v, nullptr, nullptr, nullptr);
                head = tmp;
            }
            else {
                tmp = new Node(v, nullptr, nullptr, prev);
                prev->next_orig = tmp;
                prev->next_sorted = tmp;
            }
            if (v == 0) {
                zero = tmp;
            }
            prev = tmp;
            numNodes++;
        }

        //make circular
        tmp->next_orig = head;
        tmp->next_sorted = head;
        head->prev_sorted = tmp;

        for (int g = 0; g < 10; g++) {
            tmp = head;
            for (int i = 0; i < numNodes; i++) {
                long long numSteps = (tmp->val) % (numNodes - 1);  //after numNodes-1 shifts, Node will be back to the same spot, so use modulo.
                if (numSteps >= 0) {
                    for (int j = 0; j < numSteps; j++) {
                        tmp2 = tmp->next_sorted;
                        tmp->prev_sorted->next_sorted = tmp2;
                        tmp2->next_sorted->prev_sorted = tmp;
                        tmp2->prev_sorted = tmp->prev_sorted;
                        tmp->next_sorted = tmp2->next_sorted;
                        tmp->prev_sorted = tmp2;
                        tmp2->next_sorted = tmp;
                    }
                }
                else {
                    numSteps = numSteps * -1;
                    for (int j = 0; j < numSteps; j++) {
                        tmp2 = tmp->prev_sorted;
                        tmp->next_sorted->prev_sorted = tmp2;
                        tmp2->prev_sorted->next_sorted = tmp;
                        tmp2->next_sorted = tmp->next_sorted;
                        tmp->prev_sorted = tmp2->prev_sorted;
                        tmp->next_sorted = tmp2;
                        tmp2->prev_sorted = tmp;
                    }
                }
                tmp = tmp->next_orig;
            }
        }
        coord = 0;
        tmp = zero;
        for (int i = 0; i < 1000; i++) {
            tmp = tmp->next_sorted;
        }
        cout << "NUM: " << tmp->val << endl;
        coord += tmp->val;
        for (int i = 0; i < 1000; i++) {
            tmp = tmp->next_sorted;
        }
        cout << "NUM: " << tmp->val << endl;
        coord += tmp->val;
        for (int i = 0; i < 1000; i++) {
            tmp = tmp->next_sorted;
        }
        cout << "NUM: " << tmp->val << endl;
        coord += tmp->val;
        cout << "P2: Coordinate: " << coord << endl;
        f.close();

        return 0;
    }
};