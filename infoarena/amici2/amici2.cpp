#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("amici2.in");
ofstream out("amici2.out");

const int inf = 0x3f3f3f3f, kMaxN = 22005;

int best[kMaxN], bfs[kMaxN];
vector<int> vertex[kMaxN];

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, m;
		in >> n >> m;
		for (int i = 1; i <= m; ++i) {
			int a, b;
        	in >> a >> b;
			vertex[a].push_back(b);
			vertex[b].push_back(a);
		}
		bfs[1] = 1;
		int st = 1, dr = 1;
		best[1] = 1;
		while (st <= dr) {
			int nod = bfs[st++];
			for (int i = 0; i < int(vertex[nod].size()); ++i) {
            	int oth = vertex[nod][i];
				if (not best[oth]) {
					best[oth] = best[nod] + 1;
					bfs[++dr] = oth;
				}
			}
		}

		int mx = 0;
		for (int i = 1; i <= n; ++i)
			if (mx < best[i])
				mx = best[i];

		mx--;
		int rez = 0;
		while (1 << rez < mx)
			rez++;
		out << rez << '\n';
		for (int i = 1; i <= n; ++i) {
			best[i] = 0;
			vertex[i].clear();
		}
	}
    return 0;
}
