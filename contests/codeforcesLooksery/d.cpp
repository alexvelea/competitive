//Problem d from codeforcesLooksery
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

char el[105][105];
int sum[105];
int lazy[105];

int main() {
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> el[i][j];
		}
	}
	int rez = 0;
	for (int l = n; l; --l) {
		for (int c = m; c; --c) {
			lazy[c] = lazy[c + 1] + sum[c];
			int target;
			if (el[l][c] == 'W') {
				// sum = +1;
				target = +1;
			} else {
				target = -1;
			}
			if (lazy[c] != target) {
				sum[c] += target - lazy[c];
				lazy[c] = target;
				++rez;
			}
		}
	}
	cout << rez << '\n';
	return 0;
}
