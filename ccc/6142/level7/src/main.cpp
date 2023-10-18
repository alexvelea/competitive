#include <iostream>
#include <vector>
#include "debug.hpp"

using namespace std;

char winner(char a, char b) {
    const char S = 'S', R = 'R', P = 'P', L = 'L', Y = 'Y';
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

string encoding = "SLPYR";
map<char, int> toEncoding = {
        {'S', 0},
        {'L', 1},
        {'P', 2},
        {'Y', 3},
        {'R', 4}
};

string solution[4096][20][1 << 5];

int main() {
    int t;
    cin >> t;
    int n;
    cin >> n;
    int logN = 0;
    while ((1 << logN) < n) {
        logN += 1;
    }

    for (int T = 0; T < t; T += 1) {
        string s; cin >> s;
        for (int i = 0; i < n; i += 1) {
            if (s[i] == 'X') {
                for (int j = 0; j < 5; j += 1) {
                    solution[i][0][1 << j] = encoding[j];
                }
            } else if (s[i] == 'Z') {
                solution[i][0][(1 << 5) - 1] = 'Z';
            } else {
                solution[i][0][1 << toEncoding[s[i]]] = s[i];
            }
        }

        for (int l = 1; l <= logN; l += 1) {
            for (int a = 0; a < n; a += (1 << l)) {
                int b = a + (1 << (l-1));
                for (int x = 0; x < (1 << 5); x += 1) {
                    for (int y = 0; y < (1 << 5); y += 1) {
                        if (!solution[a][l - 1][x].empty() && !solution[b][l - 1][y].empty()) {
                            int newBitmask = 0;
                            for (int b1 = 0; b1 < 5; b1 += 1) {
                                for (int b2 = 0; b2 < 5; b2 += 1) {
                                    if ((x & (1 << b1)) && (y & (1 << b2))) {
                                        newBitmask |= 1 << toEncoding[winner(encoding[b1], encoding[b2])];
                                    }
                                }
                            }

//                            cerr << l << '\t' << a << '\t' << x << '\t' << y << '\t' << newBitmask << '\n';

                            solution[a][l][newBitmask] = solution[a][l - 1][x] + solution[b][l - 1][y];
                        }
                    }
                }
            }
        }
        cout << solution[0][logN][1 << toEncoding['S']] << '\n';
//        for (int k = 0; k < (1 << 5); k += 1) {
//            cerr << k << '\t' << solution[0][logN][k] << '\n';
//        }
//        cerr << '\n';

        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < logN; j += 1) {
                for (int k = 0; k < 1 << 5; k += 1) {
                    solution[i][j][k] = "";
                }
            }
        }
    }
}