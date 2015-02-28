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

ifstream in("aint_lazy_equal.in");
ofstream out("aint_lazy_equal.out");

const int kMaxN = 100005;

struct AintNode {
	int64 sum;
	int lazy;
	bool set;
	AintNode() {
		sum = lazy = set = 0;
	}
} aint[4 * kMaxN];

int el[kMaxN];

void aint_split_node(int nod, int st, int dr) {
 	int m = (st + dr) / 2;
	if (aint[nod].set) {
		aint[2 * nod].set = true;
		aint[2 * nod + 1].set = true;

		aint[2 * nod].lazy = aint[nod].lazy;
		aint[2 * nod + 1].lazy = aint[nod].lazy;

		aint[2 * nod].sum = 1LL * (m - st + 1) * (aint[nod].lazy);	
		aint[2 * nod + 1].sum = 1LL * (dr - (m + 1) + 1) * (aint[nod].lazy);

		aint[nod].set = aint[nod].lazy = 0;
	}
}

void aint_update(int nod, int st, int dr, int c1, int c2, int val) {
	if (dr < c1 or c2 < st)
		return ;
	if (c1 <= st and dr <= c2) {
		aint[nod].lazy = val;
		aint[nod].set = true;
		aint[nod].sum = 1LL * (dr - st + 1) * val;
		return ;
	}
 	
	aint_split_node(nod, st, dr);
	int m = (st + dr) / 2;

	aint_update(2 * nod, st, m, c1, c2, val);
	aint_update(2 * nod + 1, m + 1, dr, c1, c2, val);
	aint[nod].sum = aint[2 * nod].sum + aint[2 * nod + 1].sum;
	return ;
}

void debug(int nod, int st, int dr) {
	if (aint[nod].set) {
		for (int i = st; i <= dr; ++i)
			cerr << aint[nod].lazy << ' ';
	} else {
		int m = (st + dr) / 2;
		debug(2 * nod, st, m);
		debug(2 * nod + 1, m + 1, dr);
	}
}

int64 aint_query(int nod, int st, int dr, int c1, int c2) {
	if (dr < c1 or c2 < st)
		return 0;
	if (c1 <= st and dr <= c2)
		return aint[nod].sum;
	
	aint_split_node(nod, st, dr);

	int m = (st + dr) / 2;
	int64 rez = 0;
	rez += aint_query(2 * nod, st, m, c1, c2);
	rez += aint_query(2 * nod + 1, m + 1, dr, c1, c2);
	return rez;
}


void aint_make(int nod, int st, int dr) {
	if (st == dr) {
		aint[nod].set = true;
		aint[nod].lazy = el[st];
		aint[nod].sum = el[st];
		return ;
	}
	int m = (st + dr) / 2;
	aint_make(2 * nod, st, m);
	aint_make(2 * nod + 1, m + 1, dr);
	aint[nod].sum = aint[2 * nod].sum + aint[2 * nod + 1].sum;
	return ;
}

int main() {
	int n, m;
	in >> n >> m;
 	for (int i = 1; i <= n; ++i)
		in >> el[i];
	aint_make(1, 1, n);
    while (m--) {
		int t;
		in >> t;
		if (t == 1) {
			int x, y, el;
			in >> x >> y >> el;
			aint_update(1, 1, n, x, y, el);
		} else {
			int x, y;
			int64 rez = 0;
			in >> x >> y;
			rez = aint_query(1, 1, n, x, y);
			out << rez << '\n';
		}
	}
	in.close();
	out.close();
    return 0;
}
