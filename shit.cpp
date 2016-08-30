#include <iostream>
using namespace std;

struct Perm {
    vector<int> p;
    Perm(vector<int> _p) {
        p = _p;
    }
    Perm() {
        for (int i = 0; i < 13; i += 1) {
            p.push_back(i);
        }
    }
} final({2, 1, 0, 10, 4, 7, 12, 9, 8, 11, 3, 5, 6}), currentPerm;

bool viz[13];

void back(int poz) {
    if (poz == 13) {
        
    } else {
        for (int i = 0; i < 13; i += 1) {
        }
    }
}

int main() {
    back(0);
    return 0;
}
