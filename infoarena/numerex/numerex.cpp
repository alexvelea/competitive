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

ifstream in("numerex.in");
ofstream out("numerex.out");

const int inf = 0x3f3f3f3f, kMaxN = 100005;

struct AintNode {
 	int64 sum, ratio, each_sum;
	AintNode() {
		sum = ratio = each_sum = 0;
	}
} aint[4 * kMaxN];

void aint_update(int nod, int st, int dr, int c1, int c2, int64 r, int64 each_sum) {
	if (c1 <= st and dr <= c2) {
		cerr << st << '\t' << dr << '\t' << r << '\t' << each_sum << '\n';
		aint[nod].ratio += r;
		aint[nod].sum += 1LL * each_sum * (dr - st + 1) / 2 + 1LL * r * (dr - st + 2) * (dr - st + 1) / 2;
		aint[nod].each_sum += each_sum;
		aint[nod].ratio += r;
		return ;
	}
	if (dr < c1 or c2 < st)
		return ;
	int m = (st + dr) / 2;
	aint_update(2 * nod, st, m, c1, c2, r, each_sum);
	aint_update(2 * nod + 1, m + 1, dr, c1, c2, r, each_sum + 1LL * (m - st + 1) * r);
	aint[nod].sum = aint[2 * nod].sum + aint[2 * nod + 1].sum;
	return ;
}

int64 aint_query(int nod, int st, int dr, int c1, int c2) {
	if (c1 <= st and dr <= c2)
		return aint[nod].sum;
	if (dr < c1 or c2 < st)
		return 0;

	int64 rez = 0;
	int m = (st + dr) / 2;
	rez += aint_query(2 * nod, st, m, c1, c2);
	rez += aint_query(2 * nod + 1, m + 1, dr, c1, c2);
	c1 = max(c1, st);
	c2 = min(c2, dr);
	rez += 1LL * aint[nod].each_sum * (c2 - c1 + 1);
	rez += 1LL * aint[nod].ratio * (c1 - st + 1 + c2 - st + 1) * (c2 - c1 + 1) / 2;
	return rez;
}

int main() {
	int n, m;
	in >> n >> m;
	while (m--) {
		int t;
		in >> t;
		if (t == 0) {
			int st, dr, l, k;
			in >> st >> l >> k;
			dr = st + l - 1;
			aint_update(1, 1, n, st, dr, k, 0);
		} else {
			int st, dr;
			in >> st >> dr;
			out << aint_query(1, 1, n, st, dr) << '\n';
			for (int i = 1; i <= n; ++i)
				cerr << aint_query(1, 1, n, i, i) << '\t';
			cerr << '\n';
		}
	}
    return 0;
}
