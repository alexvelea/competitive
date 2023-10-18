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

int nR, nP, nS;

void one() {
    if (nP) {
        cout << "P";
        nP -= 1;
    }
    for (int i = 0; i < 3 && nR; i += 1, nR -= 1) {
        cout << "R";
    }
}

int main() {
    int t;
    cin >> t;
    int n;
    cin >> n;
    for (int i = 0; i < t; i += 1) {
        string snr, snp, sns;
        cin >> snr >> snp >> sns;
        nR = stoi(snr.substr(0, snr.size() - 1));
        nP = stoi(snp.substr(0, snp.size() - 1));
        nS = stoi(sns.substr(0, sns.size() - 1));
        Debug(nR, nP, nS);

        for (int j = 0; j < n; j += 4) {
            one();
        }

        while (nP) {
            cout << "P";
            nP -= 1;
        }
        while (nS) {
            cout << "S";
            nS -= 1;
        }
        cout << '\n';
    }
}