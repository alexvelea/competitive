#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define ll long long

const int kMaxN = 100005, inf = 0x3f3f3f3f;

ifstream in("kami.in");
ofstream out("kami.out");

int init[kMaxN];
int step = 0;
ll val[kMaxN];

struct AintNod{
	ll sum, mx;
	AintNod() {
		sum = 0;
		mx = - 1LL * inf * inf;
	}
};

AintNod aint[8*kMaxN];

int solve(int nod, int st, int dr, int c1, int c2, ll val) {
	if (c2 < st or dr < c1)
		return 0;
	if (st == dr) {
		if (aint[nod].mx >= val)
			return st;
		return 0;
	}
	int m = (st + dr) / 2;
	if (aint[nod].mx < val)
		return 0;
	val -= aint[nod].sum;
 	if (c1 <= st and dr <= c2) {
		if (aint[2 * nod + 1].mx >= val)
			return solve(2 * nod + 1, m + 1, dr, c1, c2, val);
		return solve(2 * nod, st, m, c1, c2, val);
	} else {
		return max(solve(2 * nod, st, m, c1, c2, val),
			solve(2 * nod + 1, m + 1, dr, c1, c2, val));
	}
}

ll aint_query_el(int nod, int st, int dr, int el) {
	if (st == dr) {
		return aint[nod].sum;
	}
	int m = (st + dr) / 2;
	if (el <= m) 
		return aint[nod].sum + aint_query_el(2 * nod, st, m, el);
	else
		return aint[nod].sum + aint_query_el(2 * nod + 1, m + 1, dr, el);
}

void aint_sum_update(int nod, int st, int dr, int c1, int c2, int val) {
	if (c1 <= st and dr <= c2) {
		aint[nod].sum += 1LL * val;
		aint[nod].mx += 1LL * val;
		return ;
	}
	if (dr < c1 or c2 < st)
		return ;
	int m = (st + dr) / 2;
	aint_sum_update(2 * nod, st, m, c1, c2, val);
	aint_sum_update(2 * nod + 1, m + 1, dr, c1, c2, val);
	aint[nod].mx = max(aint[2 * nod].mx, aint[2 * nod + 1].mx) + aint[nod].sum;
	return ;
}

void aint_init(int nod, int st, int dr) {
	if (st == dr) {
		aint[nod].sum = val[st];
		aint[nod].mx = val[st];
		return ;
	}
	int m = (st + dr) / 2;
	aint_init(2 * nod, st, m);
	aint_init(2 * nod + 1, m + 1, dr);
	aint[nod].mx = max(aint[2 * nod].mx, aint[2 * nod + 1].mx);
	return ;
}

void debug(int n, ll el) {
	for (int i = 1; i <= n; ++i)
//		cerr << i << '\t' << aint_query_el(1, 1, n, i) + el << '\n';
		cerr << i << '\t' << init[i] << '\t' << aint_query_el(1, 1, n, i) + el << '\n';
	cerr << '\n';
	return ;
}

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> init[i];
	}
	ll sum = 0;
	for (int i = n; i; --i) {
		val[i] = 1LL * (init[i] - sum);
		sum += 1LL * init[i];
	}
	aint_init(1, 1, n);
/*	for (int i = 1; i <= n; ++i)
		cerr << val[i] << '\t';
	cerr << '\n';*/
	int m;
	in >> m;
 	while (m--) {
		int t;
		in >> t;
		if (t == 0) {
			int ind, x;
			in >> ind >> x;
			aint_sum_update(1, 1, n, ind, ind, x - init[ind]);
			aint_sum_update(1, 1, n, 1, ind - 1, init[ind] - x);
			init[ind] = x;
//			debug(n);
		} else {
			int ind;
			in >> ind;
			ll dr = 1LL * init[ind] - 1LL * (aint_query_el(1, 1, n, ind));
			++step;
//			cerr << dr << '\n';
			out << solve(1, 1, n, 1, ind - 1, -dr) << '\n';
		}
	}
	return 0;
}
