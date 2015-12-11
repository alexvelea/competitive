#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 50005, inf = 0x3f3f3f3f;

ifstream in("dijkstra.in");
ofstream out("dijkstra.out");

priority_queue<pair<int, int> > pq;
vector<pair<int, int> > vertex[kMaxN];

int best[kMaxN];
bool viz[kMaxN];

int main() {
	int n, m;
	in >> n >> m;
	while (m--) {
		int a, b, c;
		in >> a >> b >> c;
		vertex[a].push_back(make_pair(b, c));
	}

   	for (int i = 1; i <= n; ++i)
		best[i] = inf;
	best[1] = 0;

	pq.push(make_pair(0, 1));
	while (pq.size()) {
		int nod = pq.top().second;
		pq.pop();
		if (viz[nod])
			continue;
		for (int i = 0; i < int(vertex[nod].size()); ++i) {
			int oth = vertex[nod][i].first;
			int cost = best[nod] + vertex[nod][i].second;
			if (cost < best[oth]) {
            	best[oth] = cost;
				pq.push(make_pair(-cost, oth));
			}
		}
	}
	for (int i = 2; i <= n; ++i) 
		out << ((best[i] != inf) ? (best[i]) : (0)) << ' ';
	return 0;
}
