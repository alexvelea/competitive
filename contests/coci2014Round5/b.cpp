//Problem B from Codeforces Round coci.2014.round5
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005;

char el[kMaxN][kMaxN];
int Mn[kMaxN], Mx[kMaxN];

int main() {
    int n, m;

    cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> el[i][j];
		}
	}

	for (int i = 1; i <= n; ++i) {
		Mn[i] = m + 1;
		for (int j = 1; j <= m; ++j) {
			if (el[i][j] == 'J') {
				Mn[i] = min(Mn[i], j);
				Mx[i] = j;
			}
		}
	}
	int col = 1, rez = 0, _rez = 0;
	for (int i = n, d = 0; i; --i, d ^= 1) {
		if (d == 0) {
			if (Mx[i] != 0 or Mx[i - 1] != 0) {
				assert(col <= Mn[i]);
				int w = max(col, max(Mx[i], Mx[i - 1]));
				rez += (w - col);
				col = w;
			}
		} else {
			if (Mx[i] != 0 or Mx[i - 1] != 0) {
				assert(col >= Mx[i]);
				int w = min(min(Mn[i], Mn[i - 1]), col);
				rez += col - w;
				col = w;
			}
		}
		if (Mx[i] != 0) {
			_rez = rez;
		}
		++rez;
	}
	cout << _rez << '\n';
	return 0;
}
