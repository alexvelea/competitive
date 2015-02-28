#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("xnumere.in");
ofstream out("xnumere.out");

const int inf = 0x3f3f3f3f, kMod = 666013, kMaxN = 1005;

int Mod(int nr) {
	if (nr < 0)
		nr += kMod;
	if (nr < 0)
		nr += kMod;
	if (nr >= kMod)
		nr -= kMod;
	if (nr >= kMod)
		nr %= kMod;
	return nr;
}

int pow(int a, int64 p) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % kMod;
		p /= 2.0;
		a = (1LL * a * a) % kMod;
	}
	return rez;
}

int comb[kMaxN][kMaxN], rez[kMaxN];

int main() {
	int k, x;
	int64 n;
	in >> k >> x >> n;
	in.close();
 	for (int i = 0; i < kMaxN; ++i)
		comb[i][0] = 1;
	for (int i = 1; i < kMaxN; ++i)
		for (int j = 1; j <= i; ++j) {
			comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);
			comb[i][j] = Mod(comb[i][j]);
		}
	
	rez[1] = 1;
	for (int i = 2; i <= x; ++i) {
		rez[i] = pow(i, n);
		for (int j = 1; j < i; ++j) {
			rez[i] -= (1LL * comb[i][j] * rez[j]) % kMod;
			rez[i] = Mod(rez[i]);
		}
	}
	out << (1LL * comb[k][x] * rez[x]) % kMod;
	out.close();
    return 0;
}
