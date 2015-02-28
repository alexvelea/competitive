#include <cassert>
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

ifstream in("div4.in");
ofstream out("div4.out");

const int inf = 0x3f3f3f3f, Mod = 1000003;

void mod(int &x) {
	while (x >= Mod)
		x -= Mod;
}

int fact[Mod], invFact[Mod], ap[10];

int pow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % Mod;
		a = (1LL * a * a) % Mod;
		p /= 2;
	}
	return rez;
}

int comb(int a, int b) {
	if (a < 0 or b < 0)
		assert(0);
	if (b > a)
		swap(a, b);
	int64 rez = 1;
	rez *= 1LL *fact[a];
	rez *= 1LL * invFact[b];
	rez %= Mod;
	rez *= 1LL * invFact[a - b];
	return rez % Mod;
}

string txt;

int main() {
	int k;
	in >> txt >> k;
	fact[1] = fact[0] = invFact[1] = invFact[0] = 1;
	for (int i = 2; i <= txt.size(); ++i) {
		fact[i] = (1LL * fact[i - 1] * i) % Mod;
		invFact[i] = pow(fact[i], Mod - 2);
	}
	int rez = 0;
	for (int dr = txt.size() - 1; dr >= 0 and (int(k - (txt.size() - dr - 2)) >= 0) ; --dr) {
		int cif = txt[dr] - '0';
		for (int i = 0; i < 10; ++i) {
        	if ((cif * 10 + i) % 4 == 0) {
				rez += (1LL * ap[i] * comb(dr,int(k - (txt.size() - dr - 2)))) % Mod;
				mod(rez);
			}
		}
		ap[cif]++;
	}
	if (k == txt.size() - 1)
		rez = ap[4] + ap[8];
	out << rez << '\n';
    return 0;
}
