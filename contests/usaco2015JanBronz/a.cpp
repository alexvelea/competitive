//Problem A from Codeforces Round usaco2015JanBronz
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

const int inf = 0x3f3f3f3f, kMaxN = 10005;

ifstream in("cowroute.in");
ofstream out("cowroute.out");

int best[kMaxN], cost[kMaxN], oldBest[kMaxN];
vector<int> vertex[kMaxN];

int main() {
	int a, b, q;
    in >> a >> b >> q;
	for (int i = 1; i <= q; ++i) {
		int n;
		in >> cost[i] >> n;
		while (n--) {
			int x;
			in >> x;
			vertex[i].push_back(x);
		}
	}

	for (int i = 1; i < kMaxN; ++i)
		best[i] = inf;
	best[a] = 0;

	for (int t = 0; t < 2; ++t) {
		for (int i = 0; i < kMaxN; ++i)
			oldBest[i] = best[i];
		for (int i = 1; i <= q; ++i) {
			int mn = inf;
			for (int itr : vertex[i]) {
				mn = min(mn, oldBest[itr] + cost[i]);
				best[itr] = min(mn, best[itr]);
			}
		}
	}
	if (best[b] == inf)
		out << "-1\n";
	else
		out << best[b] << '\n';
	return 0;
}
