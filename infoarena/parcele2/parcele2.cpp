//Problem parcele2 from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005, Mod = 666013;

ifstream fin("parcele2.in");
ofstream fout("parcele2.out");

int64 aib[kMaxN][kMaxN];

int64 aibQuery(int _x, int _y) {
	int64 rez = 0;
 	for (int x = _x; x; x -= x & (-x))
		for (int y = _y; y; y -= y & (-y)) {   
			rez ^= aib[x][y];
		}
	return rez;
}

void aibUpdate(int _x, int _y, int64 val) {
	for (int x = _x; x < kMaxN; x += x & (-x))
		for (int y = _y; y < kMaxN; y += y & (-y)) {
			aib[x][y] ^= val;
		}
}

int grow[66];

int main() {
 	int t; fin >> t;
	while (t--) {
		memset(aib, 0, sizeof(aib));
		int n, m, k; fin >> n >> m >> k;
		grow[0] = 1;
		for (int i = 1; i <= 60; ++i) {
			grow[i] = (k * grow[i - 1]) % Mod;
		}
 		int p; fin >> p;
		while (p--) {
			int year; fin >> year;
			year = 2015 - year;
			if (k == 1) {
				year = 0;
			}
			int x, y; fin >> x >> y;
			aibUpdate(x, y, 1LL << year);
		}

		int q; fin >> q;
		while (q--) {
			int a, b, x, y; fin >> a >> b >> x >> y;
			int64 rez = 0;
			rez ^= aibQuery(x, y);
			rez ^= aibQuery(x, b - 1);
			rez ^= aibQuery(a - 1, y);
			rez ^= aibQuery(a - 1, b - 1);
			aibUpdate(x, y, rez);

			vector<int> fin;

            for (int i = 0; i <= 60; ++i) {
				if (rez & (1LL << i)) {
					fin.push_back(grow[i]);
				}
			}

			fout << fin.size() << ' ';
			for (auto itr : fin) {
				fout << itr << ' ';
			}
			fout << '\n';
		}
	}
	return 0;
}
