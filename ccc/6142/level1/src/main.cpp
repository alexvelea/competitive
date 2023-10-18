#include <iostream>
#include <vector>
#include "debug.hpp"

using namespace std;

const char S = 'S', R = 'R', P = 'P';

char winner(char a, char b) {
    if (a == b) {
        return a;
    }
    if (a == S && b == P) {
        return a;
    }
    if (a == P && b == R) {
        return a;
    }
    if (a == R && b == S) {
        return a;
    }
    return winner(b, a);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i += 1) {
        string s; cin >> s;
        cout << winner(s[0], s[1]) << '\n';
    }
}