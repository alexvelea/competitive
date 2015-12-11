#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second

const int kMaxN = 200005;

int aint[4 * kMaxN];

int aint_query(int nod, int st, int dr, int poz) {
	if (st == dr)
		return aint[nod];
	int m = (st + dr) / 2;
	if (poz <= m)
		return aint[nod] + aint_query(2 * nod, st, m, poz);
	else
		return aint[nod] + aint_query(2 * nod + 1, m + 1, dr, poz);
}

void aint_update(int nod, int st, int dr, int c1, int c2, int val) {
	if (c1 <= st and dr <= c2) {
		aint[nod] += val;
		return ;
	}
	if (dr < c1 or c2 < st)
		return ;
	int m = (st + dr) / 2;
	aint_update(2 * nod, st, m, c1, c2, val);
	aint_update(2 * nod + 1, m + 1, dr, c1, c2, val);
}

int nr_df;
int poz_st[kMaxN], poz_dr[kMaxN], deep[kMaxN], el[kMaxN];
bool viz[kMaxN];

vector<int> vertex[kMaxN];

void dfs(int nod) {
	++nr_df;
	poz_st[nod] = nr_df;
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int nod2 = vertex[nod][i];
		if (viz[nod2] == false) {
			deep[nod2] = deep[nod] ^ 1;
			dfs(nod2);
		}
	}
	poz_dr[nod] = nr_df;
	return ;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	dfs(1);
	while (m--) {
		int op, x, val;
		cin >> op;
		if (op == 1) {
			cin >> x >> val;
			if (deep[x] == 1)
				val *= -1;
			aint_update(1, 1, n, poz_st[x], poz_dr[x], val);
		} else {
			cin >> x;
			int y = aint_query(1, 1, n, poz_st[x]);
			if (deep[x] == 1)
				y *= -1;
            cout << el[x] + y << '\n';
		}
	}
}
