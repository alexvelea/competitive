//Problem tempest from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005, kMaxM = 300005;

ifstream in("tempest.in");
ofstream out("tempest.out");

struct Edge {
	int x, y;
	int64 time;
	int other(int nod) {
		return x + y - nod;
	}
};

vector<int> vertex[kMaxN];
Edge edge[kMaxM];

priority_queue<pair<int64, int> > pq;

int64 best[kMaxN];
bool viz[kMaxN];

int main() {
	int t; in >> t;
	while (t--) {
		int n, m, s, d; in >> n >> m >> s >> d;
 		for (int i = 1; i <= m; ++i) {
			in >> edge[i].x >> edge[i].y >> edge[i].time;
			vertex[edge[i].x].push_back(i);
			vertex[edge[i].y].push_back(i);
		}
		int k; in >> k;
		int64 tMax = 0;
		while (k--) {
			int itr; in >> itr;
			tMax += edge[itr].time;
		}

		for (int i = 1; i <= n; ++i) {
			best[i] = 1LL * inf * inf;
		}
		best[d] = 0;
		pq.push(make_pair(0, d));

		while (pq.size()) {
			int nod = pq.top().second; pq.pop();
			if (not viz[nod]) {
				viz[nod] = true;
			} else {
				continue;
			}
			
			for (auto itr : vertex[nod]) {
				int oth = edge[itr].other(nod);
				int64 cost = best[nod] + edge[itr].time;
				if (best[oth] > cost) {
					best[oth] = cost;
					pq.push(make_pair(-cost, oth));
				}
			}
		}
		
		int rez = 0;
		for (int i = 1; i <= n; ++i) {
			if (best[i] <= tMax) {
				++rez;
			}
		}
		
		out << rez << '\n';
		for (int i = 1; i <= n; ++i) {
			if (best[i] <= tMax) {
				out << i << ' ';
			}
		}
		out << '\n';

		for (int i = 1; i <= n; ++i) {
			vertex[i].clear();
			viz[i] = false;
		}
	}
	return 0;
}
