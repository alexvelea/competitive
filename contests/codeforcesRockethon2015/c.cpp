//Problem C from Codeforces Round rockethon2015
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int l[10], r[10];

double expected[10];

double expectedChx(int ind, int st, int dr) {
	st = max(st, l[ind]);
	dr = min(dr, r[ind]);
	if (st > dr)
		return 0;
	return 1.0 * (dr - st + 1) / (r[ind] - l[ind] + 1);
}


int main() {

	int n;
    cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> l[i] >> r[i];
	}

	double rez = 0.0;

	for (int i = 1; i <= 10000; ++i) {
		for (int p = 1; p < (1 << n); ++p) {
			double chx = 1.0;
			int cnt = 0;
			for (int j = 0; j < n; ++j) {
				if (p & (1 << j)) {
					cnt ++;
					chx *= expectedChx(j, i, i);
				} else {
					chx *= expectedChx(j, 0, i - 1);
				}
			}
			if (cnt == 0 or cnt == 1)
				chx = 0.0;
			rez += chx * i;
		}
//		cerr << i << '\n';
		for (int p = 0; p < n; ++p) {
//			cerr << expected[(1 << n) - (1 << p)] << '\t' << expectedChx(p, i, i) << '\t' << p << '\n';
			rez += expected[(1 << n) - (1 << p)] * expectedChx(p, i, i);
			for (int st = 1; st < (1 << n); ++st) {
				if (st & (1 << p))
					continue;
				double chx = 1.0;
				for (int l = 0; l < n; ++l) {
					if (l == p)
						continue;
					if (st & (1 << l)) {
						chx *= expectedChx(l, i, i);
					} else {
						chx *= expectedChx(l, 0, i - 1);
					}
				}
				expected[(1 << n) - (1 << p)] += 1.0 * i * chx;
			}
		}
//		cerr << "\n";
	}
	cout << fixed << setprecision(10) << 1.0 * rez << '\n';
	return 0;
}
