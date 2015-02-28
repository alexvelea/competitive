#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

#define ll long long
#define FORIT(it, v) for(vector<pair<int, int> > :: iterator it = (v).begin(); it != (v).end(); ++it)

const int kMaxC = 105, kMaxN = kMaxC * 50 * 3, inf = 0x3f3f3f3f;

ifstream in("biomech.in");
ofstream out("biomech.out");

ll min(ll a, ll b) {
	if (a < b)
		return a;
	return b;
}

void get_min (ll &a, int b) {
	if (a > b)
		a = b;
}

struct mat {
	ll el[50][50];
	mat() {
 		for (int i = 0; i < 50; ++i)
			for (int j = 0; j < 50; ++j)
				el[i][j] = 0;
	}
	mat(ll x[50][50]) {
		for (int i = 0; i < 50; ++i)
			for (int j = 0; j < 50; ++j)
				el[i][j] = 1LL * x[i][j];
	}
	mat join(mat &oth) {
		mat rez;
		for (int i = 8; i < 48; ++i)
			for (int j = 8; j < 48; ++j)
				rez.el[i][j] = 1LL * inf * inf;
		for (int i = 8; i < 48; ++i)
			for (int j = 8; j < 48; ++j)
				for (int k = 8; k < 48; ++k)
					rez.el[i][j] = min(rez.el[i][j], el[i][k] + oth.el[k][j]);
		return rez;
	}
} p[50];

int djk_best[kMaxN];
bool djk_viz[kMaxN];
priority_queue<pair<int, int> > pq;
vector<pair<int, int> > vertex[kMaxN];

ll start[50];

ll cost_next[50][50], cost_last[50][50];
int cost_dir[8][8], cost_el[6][8];

int dx[8] = {-1, -1, 0, +1, +1, +1, 0, -1};
int dy[8] = {0, +1, +1, +1, 0, -1, -1, -1};

ll n;

int node(int c, int l, int d) {
	return (c + kMaxC) * 50 + l * 8 + d;
}

bool ok (mat P) {
	ll mn;
	for (int i = 3 * 8; i < 4 * 8; ++i) {
		mn = 1LL * inf * inf;
		for (int j = 8; j < 48; ++j)
			if (mn > P.el[i][j])
				mn = P.el[i][j];
		if (mn <= 1LL * n)
			return true;
	}
	return false;
}

ll solve(mat P) {
	p[0] = P;
	for (int i = 1; i < 50; ++i)
		p[i] = p[i - 1].join(p[i - 1]);
	
    if (ok(P) == false)
		return 0;

	ll rez = 1;
	ll pw = 1LL << 49;
	for (int i = 49; i >= 0; --i, pw >>= 1) {
   		if (ok(P.join(p[i]))) {
			rez += pw;
			P = P.join(p[i]);
		}
	}
	return rez;
}

void djk(int nod) {
	for (int i = 0; i <= node(kMaxC, 5, 8); ++i) {
		djk_best[i] = inf;
		djk_viz[i] = 0;
	}
	djk_best[nod] = 0;
	pq.push(make_pair(0, nod));
	while (pq.size()) {
		int nod = pq.top().second;
		pq.pop();
		if (djk_viz[nod])
			continue;
		djk_viz[nod] = true;
		FORIT(it, vertex[nod]) {
			int c = djk_best[nod] + it->second;
			int oth = it->first;
			if (djk_best[oth] > c) {
				djk_best[oth] = c;
				pq.push(make_pair(-c, oth));
			}
		}
	}
	return ;
}

int main() {
	in >> n;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
 			in >> cost_dir[i][j];
	for (int i = 1; i <= 5; ++i)
 		for (int j = 0; j < 8; ++j)
			in >> cost_el[i][j];
	// numararea nodurilor
	// (C + max_l) * 50 + l * 8 + d
	for (int c = - kMaxC; c < kMaxC; ++c) {
		for (int l = 1; l <= 5; ++l)
			for (int d = 0; d < 8; ++d) {
				// toate cele 8 directii
				for (int D = 0; D < 8; ++D)
					if (D != d)
						vertex[node(c, l, d)].push_back(make_pair(node(c, l, D), cost_dir[d][D]));
 				int nx = l + dx[d];
				int ny = c + dy[d];
				if (nx > 0 and nx < 6 and ny >= -kMaxC  and ny < kMaxC)
					vertex[node(c, l, d)].push_back(make_pair(node(ny, nx, d), cost_el[l][d]));
			}
	}
 	for (int l = 1; l <= 5; ++l)
		for (int d = 0; d < 8; ++d) {
			int nod = node(0, l, d);
			djk(nod);
			for (int L = 1; L <= 5; ++L)
				for (int D = 0; D < 8; ++D) {
					cost_next[l * 8 + d][L * 8 + D] = djk_best[node(1, L, D)];
					cost_last[l * 8 + d][L * 8 + D] = djk_best[node(-1, L, D)];
				}
		}
	for (int l = 1; l <= 5; ++l)
		for (int d = 0; d < 8; ++d) {
			start[l * 8 + d] = 1LL * inf * inf;
			for (int D = 0; D < 8; ++D)
				get_min(start[l * 8 + d], cost_next[3 * 8 + D][l * 8 + d]);
		}
	ll a = solve(mat(cost_next));


 	for (int l = 1; l <= 5; ++l)
		for (int d = 0; d < 8; ++d) {
			start[l * 8 + d] = inf;
			for (int D = 0; D < 8; ++D)
				get_min(start[l * 8 + d], cost_last[3 * 8 + D][l * 8 + d]);
		}
	ll b = solve(mat(cost_last));
	
	out << max(a, b);
	return 0;
}
