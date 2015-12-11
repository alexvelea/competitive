//Problem produse @ 06-12-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxD = 2e5 + 5, kMod = 1e9 + 7;

#define int64 long long

ifstream fin("produse.in");
ofstream fout("produse.out");

int numberOfEls[kMaxD], ap[kMaxD];
bool isAvailable[kMaxD];
int inv[32];

void mod(int &a) {
	if (a < 0) {
		a += kMod;
	} else if (a >= kMod) {
		a -= kMod;
	}
}

int pow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1) {
			rez = (1LL * a * rez) % kMod;
		}
		p /= 2;
		a = (1LL * a * a) % kMod;
	}
	return rez;
}

int main() {
	int n, d; fin >> n >> d;
	for (int i = 1; i <= n; i += 1) {
		int x; fin >> x;
		ap[x] += 1;
	}

	int rez = pow(2, ap[1]) - 1;
	numberOfEls[1] = pow(2, ap[1]);
	
	for (int i = 1; i <= 30; i += 1) {
		inv[i] = pow(i, kMod - 2);
	}

	for (int i = 2; i < kMaxD; i += 1) {
		if (ap[i] == 0) {
			continue;
		}
		for (int initPoz = kMaxD / i; initPoz >= 1; initPoz -= 1) {
			if (not numberOfEls[initPoz]) {
				continue;
			}

			int pow = 1, currentBonus = ap[i];
			int64 exp = i;
			while (exp * initPoz < kMaxD and pow <= ap[i]) {
				numberOfEls[exp * initPoz] = (1LL * numberOfEls[initPoz] * currentBonus  + numberOfEls[exp * initPoz]) % kMod;
				exp = 1LL * exp * i;
				pow += 1;
				currentBonus = (1LL * currentBonus * (ap[i] - pow + 1)) % kMod;
				currentBonus = (1LL * currentBonus * inv[pow]) % kMod;
				
			}
		}
	}

	

	for (int i = 2; i <= d; i += 1) {
		rez += numberOfEls[i];
		mod(rez);
	}

	fout << rez << '\n';
	return 0;
}
