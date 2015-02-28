#include <iostream>
using namespace std;

const int kMaxN = 4005, kMaxM = 100005;

struct Edge {
	int a, b, c;
	Edge() {
		a = b = c = 0;
	}
    Edge(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
	}
} edge[kMaxM];

vector<pair<int, int> > vertex[kMaxN];
bool viz[kMaxN];
int RMQ[13][kMaxN], nr_RMQ;




int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b, c, t;
		cin >> a >> b >> c >> t;
 		if (t == 1) {
			vertex[a].pb(mp(b, c));
			vertex[b].pb(mp(a, c));
		} else {
			edge[++nr_e] = Edge(a, b, c);
		}
	}
	return 0;
}
