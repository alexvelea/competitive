#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
const int kMaxN = 100005, inf = 0x3f3f3f3f;
 
ifstream in("pcb.in");
ofstream out("pcb.out");
 
priority_queue<pair<int, int> > pq;
vector<pair<int, int> > vertex[kMaxN];
 
int best[kMaxN];
bool viz[kMaxN];
 
int main() {
    int n, m, x;
    in >> n >> m >> x;
	x++;
    while (m--) {
        int a, b;
        in >> a >> b;
		b++;
        vertex[a].push_back(make_pair(b, 1));
		vertex[b].push_back(make_pair(a, 1));
    }
 
    for (int i = 1; i <= n + 1; ++i)
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
	if (best[x] == inf)
		out << "-1\n";
	else
		out << best[x];
    return 0;
}
