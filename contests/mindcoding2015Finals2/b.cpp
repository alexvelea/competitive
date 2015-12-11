//Problem b from mindcodingFinalRound2
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005;

int el[kMaxN][kMaxN];
int L[kMaxN][kMaxN], R[kMaxN][kMaxN];
int downR[kMaxN][kMaxN], downL[kMaxN][kMaxN];

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> el[i][j];
		}
	}
    int mx = el[1][1];

	for (int l = 1; l <= n; ++l) {
		for (int c = 1; c <= n; ++c) {
			downR[l][c] = max(downR[l - 1][c], R[l - 1][c]) + el[l][c];
			downL[l][c] = max(downL[l - 1][c], L[l - 1][c]) + el[l][c];
		}
		for (int c = 1; c <= n; ++c) {
			// right move
			if (c > 1) {
	 			R[l][c] = max(R[l][c - 1], downL[l][c - 1]) + el[l][c];
				mx = max(R[l][c], mx);
			} else {
				R[l][c] = -inf;
			}
		}
		for (int c = n; c; --c) {
			if (c != n) {
				L[l][c] = max(L[l][c + 1], downR[l][c + 1]) + el[l][c];
				mx = max(L[l][c], mx);
			} else {
				L[l][c] = -inf;
			}
		}
	}
	cout << mx << '\n';
	return 0;
}
