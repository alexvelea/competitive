#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("reinvent.in");
ofstream out("reinvent.out");

const int kMaxN = 100005, inf = 0x3f3f3f3f;
vector<int> vertex[kMaxN];
int best[kMaxN], from[kMaxN], bfs[kMaxN];

int main() {
	int n, m, x;
	in >> n >> m >> x;
	while (m--) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i) {
		best[i] = inf;
		from[i] = 0;
	}
	int st = 1, dr = 0;
	for (int i = 1; i <= x; ++i) {
		int el;
		in >> el;
		best[el] = 0;
		from[el] = el;
		bfs[++dr] = el;
	}
	int mn = inf;
	while (st <= dr) {
		int nod = bfs[st++];
		for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
			int oth = vertex[nod][itr];
			if (best[oth] == inf) {
	        	best[oth] = best[nod] + 1;
				from[oth] = from[nod];
				bfs[++dr] = oth;
			} else {
				if (from[oth] != from[nod] and best[nod] + best[oth] + 1 < mn)
					mn = best[nod] + best[oth] + 1;
			}
		}
	}
	out << mn << '\n';
	return 0;
}
