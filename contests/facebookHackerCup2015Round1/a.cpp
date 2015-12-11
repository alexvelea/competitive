//Problem A from Codeforces Round facebookHackerCup2015Round1
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
//#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 10000005;

int prim[kMaxN];
int rez[9][kMaxN];

ifstream cin("input.txt");
ofstream cout("output.txt");

int main() {
	int t;
    cin >> t;

	for (int i = 2; i < kMaxN; ++i) {
		if (prim[i] == 0) {
			for (int j = i; j < kMaxN; j += i) {
				prim[j]++;
			}
		}
	}

	for (int i = 1; i < kMaxN; ++i) {
		for (int j = 0; j < 9; ++j)
			rez[j][i] = rez[j][i - 1];
		rez[prim[i]][i]++;
	}
	for (int T = 1; T <= t; ++T) {
		int a, b, k;
		cin >> a >> b >> k;
		--a;

		int _rez = 0;

		if (k >= 9) {
			_rez = 0;
		} else {
			_rez = rez[k][b] - rez[k][a];
		}

		cout << "Case #" << T << ": " << _rez << '\n';
	}
	return 0;
}
