#include <iostream>
#include <vector>
#include <algorithm>

#define maxn 1000010
#define maxq 300010
#define maxe (1<<22)

using namespace std;

struct Edge {
	int x, y, c;
	Edge() {}
	Edge(int x, int y, int c) : x(x), y(y), c(c) {}

	bool operator < (const Edge& other) {
		return c > other.c;
	}
} edges[maxe], q[maxq];
int pos[maxq];
int t, nodes;
int best[1010][1010], pre[1010][1010], name[1010][1010];
char s[1010][1010];
int Q, n;

bool bad(int i) {
	return (!(1 <= i && i <= n));
}

int rect(int i, int j, int ii, int jj) {
	if (bad(i) || bad(j) || bad(ii) || bad(jj))
		return 0;
	return pre[i][j] - pre[ii-1][j] - pre[i][jj-1] + pre[ii-1][jj-1];
}

void build_graph() {
	nodes = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1] + (s[i][j] == '#' ? 0 : 1);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s[i][j] == '#')
				best[i][j] = 0;
			else {
				name[i][j] = ++nodes;
				int lo = 0, hi = n;
				while (hi - lo > 1) {
					int mid = (lo + hi)/2;
					if (rect(i+mid, j+mid, i-mid, j-mid) == (2*mid+1)*(2*mid+1))
						lo = mid;
					else hi = mid;
				}
				best[i][j] = (2*lo+1);
			}
			// cout << best[i][j] << " ";
		}
		// cout << "\n";
	}

	vector<int> dir1 = {0, 1};
	vector<int> dir2 = {1, 0};
	t = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s[i][j] == '#')
				continue;
			for (int k = 0; k < dir1.size(); ++k) {
				int ii = i + dir1[k];
				int jj = j + dir2[k];
				if (s[ii][jj] == '#')
					continue;
				edges[++t] = Edge(name[i][j], name[ii][jj], min(best[i][j], best[ii][jj]));
			}
		}
	}
}

int f[maxn], d[maxn];

int parent(int x) {
	if (f[x]) {
		return f[x] = parent(f[x]);
	}
	return x;
}

void unite(int a, int b) {
	a = parent(a);
	b = parent(b);

	if (a != b) {
		if (d[a] < d[b]) {
			f[a] = b;
		} else {
			f[b] = a;
			if (d[a] == d[b])
				++d[a];
		}
	}
}

bool united(int a, int b) {
	return parent(a) == parent(b);
}

vector<int> B[2][maxe];

void reset_dsu() {
	for (int i = 1; i <= nodes; ++i) {
		f[i] = 0;
		d[i] = 0;
	}
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i]+1);
		s[i][0] = s[i][n+1] = '#';
	}
	for (int i = 1; i <= n; ++i) {
		s[0][i] = '#';
		s[n+1][i] = '#';
	}

	build_graph();
	sort(edges + 1, edges + t + 1);

	// for (int i = 1; i <= t; ++i) {
	// 	cout << edges[i].c << "\n";
	// }
	// cout.flush();

	scanf("%d", &Q);

	int lg = 0;
	for (; (1<<lg) <= t; ++lg);

	for (int i = 1; i <= Q; ++i) {
		int ai, aj, bi, bj;
		scanf("%d %d %d %d", &ai, &aj, &bi, &bj);
		q[i].x = name[ai][aj];
		q[i].y = name[bi][bj];
		B[0][1<<(lg-1)].push_back(i);
		pos[i] = (1<<(lg-1));
	}

	int ok = 0;
	for (int i = lg-1; i >= 0; --i, ok = 1-ok) {
		for (int j = 0; j < (1<<lg); ++j) {
			B[1-ok][j].clear();
		}
		reset_dsu();

		for (int j = 1; j < (1<<lg); ++j) {
			if (j <= t)
				unite(edges[j].x, edges[j].y);

			for (auto& wh : B[ok][j]) {
				int new_pos = j + (i != 0 ? (1<<(i-1)) : 0);
				if (united(q[wh].x, q[wh].y)) {
					new_pos -= (1<<i);
				}
				B[1-ok][new_pos].push_back(wh);
				pos[wh] = new_pos;
			}
		}
	}

	for (int i = 1; i <= Q; ++i) {
		if (pos[i] >= t) {
			cout << 0 << "\n";
		} else {
			cout << edges[pos[i]+1].c << "\n";
		}
	}
}

int main() {
	int k = 1;
	for (; k <= 1; ++k) {
		solve();
	}
}