//Problem vlad from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 805;

ifstream in("vlad.in");
ofstream out("vlad.out");

vector<pair<int, int> > vertex[kMaxN];
int dp[kMaxN][kMaxN], d[kMaxN];
bool inside[kMaxN][kMaxN];

int main() {
	int p, n, m; in >> p >> n >> m;
	for (int i = 1; i <= n; ++i) 
		in >> d[i];
	for (int i = 1; i <= m; ++i) {
		int a, b, c; in >> a >> b >> c;
		vertex[a].push_back(make_pair(b, c));
		vertex[b].push_back(make_pair(a, c));
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = inf;
		}
	}
	dp[1][1] = 0;
	queue<pair<int, int> > q;
	q.push(make_pair(1, 1));
	while (q.size()) {
		int nod = q.front().first;
		int dragon = q.front().second;
		q.pop();
		inside[nod][dragon] = false;
		for (auto itr : vertex[nod]) {
			if (itr.second <= d[dragon]) {
				int cost = dp[nod][dragon] + itr.second;
				if (dp[itr.first][dragon] > cost) {
					dp[itr.first][dragon] = cost;
					if (not inside[itr.first][dragon]) {
						inside[itr.first][dragon] = true;
						q.push(make_pair(itr.first, dragon));
					}
				}

				if (dp[itr.first][itr.first] > cost) {
					dp[itr.first][itr.first] = cost;
					if (not inside[itr.first][itr.first]) {
						inside[itr.first][itr.first] = true;
						q.push(make_pair(itr.first, itr.first));
					}
				}
			}
		}
	}

	int mn = inf;
	for (int i = 1; i <= n; ++i) {
		mn = min(mn, dp[n][i]);
	}
	out << mn << '\n';
	return 0;
}
