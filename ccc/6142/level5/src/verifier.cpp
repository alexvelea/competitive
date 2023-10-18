#include <iostream>
#include <vector>
#include "debug.hpp"

using namespace std;

const char S = 'S', R = 'R', P = 'P', L = 'L', Y = 'Y';

char winner(char a, char b) {
    if (a == b) {
        return a;
    }
    if (a == S && (b == P || b == L)) {
        return a;
    }
    if (a == P && (b == R || b == Y)) {
        return a;
    }
    if (a == R && (b == S || b == L)) {
        return a;
    }
    if (a == L && (b == P || b == Y)) {
        return a;
    }
    if (a == Y && (b == R || b == S)) {
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
        string ss = "";
        while (s.size() > 1) {
            ss = "";
            for (int j = 0; j < s.size(); j += 2) {
                ss += winner(s[j], s[j + 1]);
            }
            s = ss;
            Debug(s);
        }

        if (s != "S") {
            cout << i + 1 << '\t' << s << '\n';
        }
    }
}