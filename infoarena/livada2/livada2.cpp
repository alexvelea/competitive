//Problem livada2 from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 305;

ifstream in("livada2.in");
ofstream out("livada2.out");

int dp[kMaxN][kMaxN], el[kMaxN][kMaxN], up[kMaxN];

void init(int m) {
	for (int st = 1; st <= m; ++st) {
		for (int dr = st; dr <= m; ++dr) {
			dp[st][dr] = -inf;
		}
	}
}

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, m;
		in >> n >> m;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				in >> el[i][j];
			}
		}
		int rez = -inf;
		for (int i = 1; i <= n; ++i) {
			init(m);
			for (int st = 1; st <= m; ++st) {
				int mx = 0, sum = 0;
				for (int dr = st; dr <= m; ++dr) {
					sum += el[i][dr];
					if (mx < up[dr])
						mx = up[dr];
					dp[st][dr] = sum + mx;
					if (sum + mx > rez)
						rez = sum + mx;
				}
			}
			for (int l = m; l; --l) {
				for (int st = 1; st + l <= m; ++st) {
					int dr = st + l;
					getMax(dp[st][dr - 1], dp[st][dr]);
					getMax(dp[st + 1][dr], dp[st][dr]);
				}
			}
			for (int j = 1; j <= m; ++j)
				up[j] = dp[j][j];
		}
		out << rez << '\n';
		for (int j = 1; j <= m; ++j)
			up[j] = 0;
	}
	return 0;
}
