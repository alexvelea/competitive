//Problem pavare from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 155, kMaxM = 15;

ifstream in("pavare.in");
ofstream out("pavare.out");

int ok[kMaxN][kMaxM];
int dp[kMaxN][kMaxM][1 << kMaxM];

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int n, m, k;
	in >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ok[i][j] = true;
		}
	}

	while (k--) {
		int a, b;
		in >> a >> b;
		a--;
		b--;
		ok[a][b] = false;
		if (b) {
			ok[a][b - 1] = false;
		}
		if (a) {
			ok[a - 1][b] = false;
		}
		if (a & b) {
			ok[a - 1][b - 1] = false;
		}
	}

 	for (int l = 0; l < n; ++l) {
		for (int c = 0; c < m; ++c) {
			int ln = l, cn = c + 1;
			if (cn == m) {
				ln++;
				cn = 0;
			}
			
			int ln2 = l, cn2 = cn + 1;
			if (cn2 == m) {
				ln2++;
				cn2 = 0;
			}

			for (int t = 0; t < (1 << m); ++t) {
 				if (t & (1 << c)) {
					getMax(dp[ln][cn][t ^ (1 << c)], dp[l][c][t]);
				} else {
					getMax(dp[ln][cn][t], dp[l][c][t]);
					if (c + 1 < m and (t & (1 << (c + 1))) == 0 and ok[l][c]) {
						getMax(dp[ln2][cn2][t | ((1 << c) | (1 << (c + 1)))], dp[l][c][t] + 1);
					}
				}
			}
		}
	}
	out << dp[n][0][0] << '\n';
	return 0;
}
