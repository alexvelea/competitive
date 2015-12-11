//Problem C from Codeforces Round usaco2014JanSilver
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 105;

bitset<100 * kMaxN> dp[2][kMaxN];
int dist[2][kMaxN][kMaxN];

ifstream in("meeting.in");
ofstream out("meeting.out");

void solve(int ind, int st, int n) {
	dp[ind][st][0] = true;
	for (int i = st; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (dist[ind][i][j])  {
				dp[ind][j] |= (dp[ind][i] << dist[ind][i][j]);
			}
		}
	}
}

int main() {
	int n, m;
    in >> n >> m;
	while (m--) {
		int x, y, a, b;
		in >> x >> y >> a >> b;
		dist[0][x][y] = a;
		dist[1][x][y] = b;
	}
	
	solve(0, 1, n);
	solve(1, 1, n);

	for (int i = 0; i <= 100 * n; ++i) {
		if (dp[0][n][i] == true and dp[1][n][i] == true) {
			out << i << '\n';
			return 0;
		}
	}
	out << "IMPOSSIBLE";
	return 0;
}
