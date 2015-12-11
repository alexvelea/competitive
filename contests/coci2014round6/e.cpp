//Problem E from Codeforces Round coci2014round6
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

int dp[kMaxN][kMaxN], el[kMaxN][kMaxN];

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> el[i][j];
		}
	}

	for (int l = 2; l <= n; ++l) {
		for (int c = 2; c <= m; ++c) {
			if (el[l][c]+ el[l - 1][c - 1] <= el[l][c - 1] + el[l - 1][c]) {
				dp[l][c] = dp[l][c - 1] + 1;
			}
		}
	}

	int mx = 1;

	for (int c = 2; c <= m; ++c) {
		vector<int> bonus(n + 5), deq(n + 5);
		int dr = 1;
		for (int l = 2; l <= n + 1; ++l) {
			while (dr and dp[deq[dr]][c] > dp[l][c]) {
				bonus[deq[dr]] += l - deq[dr] - 1;
				--dr;
			}
			deq[++dr] = l;
		}
		dr = 0;
		for (int l = n; l >= 1; --l) {
			while (dr and dp[deq[dr]][c] > dp[l][c]) {
				bonus[deq[dr]] += deq[dr] - l - 1;
				--dr;
			}
			deq[++dr] = l;
		}
		for (int l = 1; l <= n; ++l) {
			getMax(mx, (bonus[l] + 2) * (dp[l][c] + 1));
//			cerr << bonus[l] << '\t';
		}
//		cerr << '\n';
//		cerr << '\n';		
	}
//	for (int l = 1; l <= n; ++l, cerr << "\n")
//		for (int c = 1; c <= m; ++c)
//			cerr << dp[l][c] << '\t';
	if (mx == 1)
		mx = 0;
	cout << mx << '\n';
	
	
	return 0;
}
