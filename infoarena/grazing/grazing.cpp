#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
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

ifstream in("grazing.in");
ofstream out("grazing.out");

const int inf = 0x3f3f3f3f, kMaxCif = 800, Sigma = 1000000000, kMaxN = 305;

void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

string to_string_zero(int val) {
	string txt = "000000000";
	int i = 8;
	while (val) {
		txt[i--] = (val % 10) + '0';
		val /= 10;
	}
 	return txt;
}

struct BigNumber {
	int cif[kMaxCif], nrCif;
	BigNumber() {
		for (int i = 0; i < kMaxCif; ++i)
			cif[i] = 0;
		nrCif = 1;
	}
	BigNumber(int _x) {
		for (int i = 0; i < kMaxCif; ++i)
			cif[i] = 0;
		cif[0] = _x;
		nrCif = 1;
	}

	inline void push (int poz, int64 val) {
		val += 1LL * cif[poz];
		cif[poz] = val % Sigma;
		if (val >= Sigma)
			push(poz + 1, val / Sigma);
		else
			if (nrCif < poz + 1)
				nrCif = poz + 1;
	}

	BigNumber operator + (const BigNumber &rhs) const {
    	BigNumber rez;
		for (int i = 0; i < max(nrCif, rhs.nrCif); ++i) {
			int act = cif[i] + rhs.cif[i];
			rez.push(i, act);
		}
		return rez;
	}

	BigNumber operator * (const BigNumber &rhs) const {
		BigNumber rez;
		for (int i = 0; i < nrCif; ++i)
			for (int j = 0; j < rhs.nrCif; ++j) {
				int64 act = (1LL * cif[i] * rhs.cif[j]);
				rez.push(i + j, act);
			}
		return rez;
	}
	
	BigNumber operator * (const int &rhs) const {
		BigNumber rez;
		for (int i = 0; i < nrCif; ++i) {
        	int64 act = 1LL * rhs * cif[i];
			rez.push(i, act);
		}
		return rez;
	}

	string show() {
    	string rez = to_string(cif[nrCif - 1]);
		for (int i = nrCif - 2; i >= 0; --i)
			rez += to_string_zero(cif[i]);
		return rez;
	}
} comb[kMaxN][kMaxN], fact[kMaxN], rez[kMaxN];
 



int main() {
	for (int i = 0; i < kMaxN; ++i)
		comb[i][0] = BigNumber(1);
	for (int i = 1; i < kMaxN; ++i)
		for (int j = 1; j <= i; ++j)
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];

	fact[0] = fact[1] = fact[2] = BigNumber(1);
	for (int i = 3; i < kMaxN; ++i) {
		fact[i] = fact[i - 1] * i;
	}

	rez[0] = BigNumber(1);
	for (int n = 1; n <= 300; ++n) {
		for (int i = 1; i <= n; ++i)
			rez[i] = BigNumber(0);
		for (int i = 0; i <= n; ++i) 
			for (int l = 1; l + i <= n; ++l) {
				rez[i + l] = rez[i + l] + rez[i] * (comb[n - i - 1][l - 1]) * fact[l];
				if (l > 3 and (l % 3 != 0))
					rez[i + l] = rez[i + l] + rez[i] * (comb[n - i - 1][l - 1]) * fact[l - 1];
			}
		out << "\"" << rez[n].show() << "\", ";
	}
	return 0;
}
