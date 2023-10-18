#include <iostream>
#include <vector>
#include "debug.hpp"

using namespace std;

//const char S = 'S', R = 'R', P = 'P';
//
//char winner(char a, char b) {
//    if (a == b) {
//        return a;
//    }
//    if (a == S && b == P) {
//        return a;
//    }
//    if (a == P && b == R) {
//        return a;
//    }
//    if (a == R && b == S) {
//        return a;
//    }
//    return winner(b, a);
//}

int nR, nP, nS, nY, nL;

void consume(string s) {
    for (char c : s) {
        if (nS && c == 'S') {
            cout << "S";
            nS -= 1;
            return;
        } else if (nR && c == 'R') {
            cout << "R";
            nR -= 1;
            return;
        } else if (nY && c == 'Y') {
            cout << "Y";
            nY -=1 ;
            return;
        } else if (nP && c == 'P') {
            cout << "P";
            nP -= 1;
            return;
        } else if (nL && c == 'L') {
            cout << "L";
            nL -= 1;
            return;
        }
    }
    cerr << "PANIC!\n";
}

void solveP(int l) {
    int put = 1;
    while (put + nR + nY < (1 << l)) {
        put += 1;
        consume("SLP");
    }
    for (int p = 0; p + put < (1 << l); p += 1) {
        consume("RY");
    }
    cout << "P";
}

void solveL(int l) {
    for (int j = l-1; j >= 0; j -= 1) {
        bool ok = false;
        if (nY) {
            ok = true;
            cout << "Y";
            nY -= 1;
        }

        for (int p = 0; p +ok < (1 << j); p += 1) {
            consume("RYLPS");
        }
    }
    cout << "L";
}

void solve(int l) {
    auto one = [&]() {
        if (nS) {
            cout << "S";
            nS -= 1;
        } else if (nR){
            cout << "R";
            nR -= 1;
        } else if (nY) {
            cout << "Y";
            nY -=1 ;
        } else if (nL) {
            cout << "L";
            nL -= 1;
        } else {
            cout << "P";
            nP -= 1;
        }
    };

    if (nP && ((1 << l) - 1) <= (nR + nY)) {
        nP -= 1;
        int put = 1;
        while (put + nR + nY < (1 << l)) {
            put += 1;
            consume("SLP");
        }
        for (int p = 0; p + put < (1 << l); p += 1) {
            consume("RY");
        }
        cout << "P";
    } else {
        nL -= 1;
        for (int j = l-1; j >= 0; j -= 1) {
            bool ok = false;
            if (nY) {
                ok = true;
                cout << "Y";
                nY -= 1;
            }

            for (int p = 0; p +ok < (1 << j); p += 1) {
                consume("RYLPS");
            }
        }
        cout << "L";
    }
}

int main() {
    int t;
    cin >> t;
    int n;
    cin >> n;
    int logN = 0;
    while ((1 << logN) < n) {
        logN += 1;
    }

    for (int i = 0; i < t; i += 1) {
        string snr, snp, sns, sny, snl;
        cin >> snr >> snp >> sns >> sny >> snl;
        nR = stoi(snr.substr(0, snr.size() - 1));
        nP = stoi(snp.substr(0, snp.size() - 1));
        nS = stoi(sns.substr(0, sns.size() - 1));
        nY = stoi(sny.substr(0, sny.size() - 1));
        nL = stoi(snl.substr(0, snl.size() - 1));
        Debug(nR, nP, nS, nY, nL);

        int depth = 0;
        while ((1 << depth) <= nS) {
            depth += 1;
        }
        depth -= 1;
        nS -= (1 << depth);

        vector<bool> isP;

        for (int j = logN-1; j >= depth; j -= 1) {
            if (nP > 0) {
                nP -= 1;
                isP.push_back(true);
            } else {
                nL -= 1;
                isP.push_back(false);
            }
        }
        int j = logN-1;
        for (auto isp : isP) {
            if (isp) {
                solveP(j);
            } else {
                solveL(j);
            }
            j -= 1;
        }
//        for (int j = logN-1; j >= depth; j -= 1) {
//            solve(j);
//            for (int p = 0; p + 1 < (1 << j); p += 1) {
//                one();
//            }
//            if (nP) {
//                cout << "P";
//                nP -= 1;
//            } else if (nL) {
//                cout << "L";
//                nL -= 1;
//            } else {
//                cerr << "FAIL?!\n";
//            }
//        }

        for (int j = 0; j < (1 << depth); j += 1) {
            cout << "S";
        }

        cout << '\n';
    }
}