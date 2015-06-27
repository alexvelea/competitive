//Problem permsplitcount @ 27-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1505;
int Mod;

#define int64 long long

ifstream fin("permsplitcount.in");
ofstream fout("permsplitcount.out");

int fact[kMaxN], fixedSeq[kMaxN], answerSeq[kMaxN];

void compute() {
    fact[0] = 1;
    for (int i = 1; i < kMaxN; ++i) {
        fact[i] = (1LL * fact[i - 1] * i) % Mod;
    }
}

void simpleMod(int &a) {
    if (a >= Mod) {
        a -= Mod;
    } else if (a < 0) {
        a += Mod;
    }
}

int main() {
    int n; fin >> n >> Mod;
	compute();

    answerSeq[0] = 1;
    answerSeq[1] = 1;
    answerSeq[2] = 1;
    for (int i = 3; i <= n; ++i) {
//        answerSeq[i] = (2 * answerSeq[i - 1]) % Mod;
        answerSeq[i] = 0;
        for (int itr = 1; itr < i; ++itr) {
//            answerSeq[i] += (2LL * answerSeq[itr - 1] * answerSeq[i - itr]) % Mod;
            int exp = 2;
            if (i - itr == 1) {
                exp = 1;
            } 
            answerSeq[i] += (exp * 1LL * answerSeq[itr] * answerSeq[i - itr]) % Mod;
            simpleMod(answerSeq[i]);
        }
        
        simpleMod(answerSeq[i]);
    }

//   for (int i = 1; i <= n; ++i) {
//        cerr << answerSeq[i] << '\n';
//    }
    answerSeq[n] = (fact[n] - 2 * answerSeq[n]) % Mod;
    simpleMod(answerSeq[n]);
    fout << answerSeq[n] << '\n';
    return 0;
}
