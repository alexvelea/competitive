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
    int t;
    cin >> t;
    int n;
    cin >> n;
    for (int i = 0; i < t; i += 1) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j += 4) {
            cout << winner(winner(s[j], s[j + 1]), winner(s[j+2], s[j + 3]));
        }
        cout << '\n';
    }
}