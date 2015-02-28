//Problem kgraf from Infoarena
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

ifstream in("kgraf.in");
ofstream out("kgraf.out");

int topo[kMaxN], dp[kMaxN][kMaxN], oldDp[kMaxN][kMaxN];
bool viz[kMaxN];
vector<pair<int, int> > vertex[kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		if (not viz[itr.first]) {
			df(itr.first);
		}
	}
	topo[++topo[0]] = nod;
}

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int n, m, k;
	in >> n >> m >> k;
	while (m--) {
		int a, b, c;
		in >> a >> b >> c;
		vertex[a].push_back(make_pair(b, c));
	}
	for (int i = 1; i <= n; ++i) {
		if (not viz[i]) {
			df(i);
		}
	}
	reverse(topo + 1, topo + n + 1);
 	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= k; ++j)
			dp[i][j] = -inf;

	for (int t = 0; t <= k; ++t) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= k; ++j) {
				oldDp[i][j] = dp[i][j];
				dp[i][j] = -inf;
			}
		}
		for (int i = 1; i <= n; ++i) {
			int nod = topo[i];
			for (auto itr : vertex[nod]) {
				for (int j = 0; j <= k; ++j) {
//					getMax(dp[itr.first][j], dp[nod][j]);
//					getMax(dp[itr.first][j + 1], dp[nod][j] + itr.second);
					getMax(dp[itr.first][j], oldDp[nod][j] - itr.second);
					getMax(dp[itr.first][j + 1], oldDp[nod][j]);

					getMax(oldDp[itr.first][j + 1], oldDp[nod][j] + itr.second);
					getMax(oldDp[itr.first][j], oldDp[nod][j]);
				}
			}
		}
/*		for (int i = 1; i <= n; ++i) {
			cerr << topo[i] << '\t';
			for (int j = 0; j <= k; ++j)
				cerr << dp[topo[i]][j] << '\t';
			cerr << '\n';
		}*/
	}

	int mx = -inf;
	for (int i = 1; i <= n; ++i)
		getMax(mx, oldDp[i][k]);
//	getMax(mx, -1);
	out << mx << '\n';
	return 0;
}
