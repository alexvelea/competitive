//Problem algoritm from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 200005;

ifstream in("algoritm.in");
ofstream out("algoritm.out");

int64 best[kMaxN];

struct Edge {
	int x, y, cost, id;
	bool operator < (const Edge &rhs) const {
		return best[x] < best[rhs.x];
	}
} edge[kMaxN];

vector<int> edgeId[kMaxN];
bool viz[kMaxN];
priority_queue<pair<int64, int> > pq;

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, m;
		in >> n >> m;
		for (int i = 1; i <= n; ++i) {
			edgeId[i].clear();
		}
		for (int i = 1; i <= m; ++i) {
			in >> edge[i].x >> edge[i].y >> edge[i].cost;
			edge[i].id = i;
			edgeId[edge[i].x].push_back(i);
		}
		for (int i = 1; i <= n; ++i) {
			best[i] = 1LL * inf * inf;
			viz[i] = false;
		}
		best[1] = 0;
		pq.push(make_pair(0, 1));
		while (pq.size()) {
			int nod = pq.top().second;
			pq.pop();
			if (viz[nod])
				continue;
			viz[nod] = true;
			for (auto itr : edgeId[nod]) {
				int oth = edge[itr].y, cost = edge[itr].cost;
				if (best[oth] > best[nod] + cost) {
			   		best[oth] = best[nod] + cost;
					pq.push(make_pair(-best[oth], oth));
				} 
			}
		}
		sort(edge + 1, edge + m + 1);
		for (int i = 1; i <= m; ++i) {
			out << edge[i].id << ' ';
		}
		out << '\n';
	}
	return 0;
}
