#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("reinvent.in");
ofstream out("reinvent2.out");

const int kMaxN = 100005, inf = 0x3f3f3f3f;

vector<int> vertex[kMaxN];
int bfs[kMaxN], best[kMaxN];
bool good[kMaxN];

int main() {
	int n, m, x;
	in >> n >> m >> x;
	while (m--) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	for (int i = 1; i <= x; ++i) {
		int el;
    	in >> el;
		good[el] = true;
	}
	int mn = inf;
	for (int i = 1; i <= n; ++i) {
		if (not good[i])
			continue;
		for (int j = 1; j <= n; ++j)
			best[j] = inf;
		int dr = 0, st = 1;
		bfs[++dr] = i;
		best[i] = 0;
		while (st <= dr) {
			int nod = bfs[st++];
			for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
				int oth = vertex[nod][itr];
				if (good[oth] and oth != i) {
					mn = min(mn, best[nod] + 1);
					st = inf;
					break;
				}
				if (best[oth] == inf) {
					best[oth] = best[nod] + 1;
					bfs[++dr] = oth;
				}
			}
		}
	}
	out << mn << '\n';
	return 0;
}
