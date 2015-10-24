//Problem scenariu @ 16-07-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMod = 666013, kMaxN = 1e4 + 5;

#define int64 long long

ifstream fin("scenariu.in");
ofstream fout("scenariu.out");

int pow(int a, int p) {
    int rez = 1;
    while (p) {
        if (p & 1) {
            rez = (1LL * rez * a) % kMod;
        }
        p /= 2;
        a = (1LL * a * a) % kMod;
    }
    return rez;
}

int fact[kMaxN];

int main() {
    int n, m, k = 0;
    fact[0] = 1;
    for (int i = 1; i < kMaxN; ++i) {
        fact[i] = (1LL * i * fact[i - 1]) % kMod;
    }

    fin >> n >> m;
    while (m--) {
        int aux; fin >> aux;
        k += aux;
    }

    n--; k--;
    int rez = fact[n];
    rez = (1LL * rez * pow(fact[k], kMod - 2)) % kMod;
    rez = (1LL * rez * pow(fact[n - k], kMod - 2)) % kMod;

    fout << rez << '\n';
	return 0;
}
