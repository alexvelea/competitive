//Problem #C from Codeforces MindcodingFinal1
#include <cmath>
#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 100005;

ifstream in("date.in");
ofstream out("date2.out");

struct AintNode {
	int lazy, under[2];
} aint[4 * kMaxN];

void build_aint(int nod, int st, int dr) {
    aint[nod].under[0] = dr - st + 1;
	if (st == dr)
		return ;
	int m = (st + dr) / 2;
	build_aint(2 * nod, st, m);
	build_aint(2 * nod + 1, m + 1, dr);
}

void aint_update(int nod, int st, int dr, int c1, int c2) {
	if (c2 < st or dr < c1)
		return ;
	if (c1 <= st and dr <= c2) {
    	aint[nod].lazy ^= 1;
		return ;
	}
	int m = (st + dr) / 2;
	aint_update(2 * nod, st, m, c1, c2);
	aint_update(2 * nod + 1, m + 1, dr, c1, c2);
	for (int i = 0; i < 2; ++i)
		aint[nod].under[i] = 0;
	for (int i = 0; i < 2; ++i) {
		aint[nod].under[i] += aint[2 * nod].under[(i + aint[2 * nod].lazy) % 2];
 		aint[nod].under[i] += aint[2 * nod + 1].under[(i + aint[2 * nod + 1].lazy) % 2];    	
	}
	return ;
}

int get_val(int nod, int st, int dr, int c) {
	if (st == dr)
		return aint[nod].lazy;
	int m = (st + dr) / 2;
	if (c <= m)
		return aint[nod].lazy ^ get_val(2 * nod, st, m, c);
	else
		return aint[nod].lazy ^ get_val(2 * nod + 1, m + 1, dr, c);
}

int get_st(int nod, int st, int dr, int c, int v) {
	v ^= aint[nod].lazy;
	if (st == dr) {
		return aint[nod].under[v];
	}
	if (dr == c) {
		if (aint[nod].under[v] == (dr - st + 1))
			return dr - st + 1;
	}
	int m = (st + dr) / 2;
	if (c <= m)
		return get_st(2 * nod, st, m, c, v);
	int x = get_st(2 * nod + 1, m + 1, dr, c, v);
	if (x == (c - (m + 1) + 1))
		return x + get_st(2 * nod, st, m, m, v);
	return x;
}

int get_dr(int nod, int st, int dr, int c, int v) {
	v ^= aint[nod].lazy;
	if (st == dr) {
		return aint[nod].under[v];
	}
	if (st == c) {
		if (aint[nod].under[v] == (dr - st + 1))
			return dr - st + 1;
	}
	int m = (st + dr) / 2;
	if (c > m)
		return get_dr(2 * nod + 1, m + 1, dr, c, v);
	int x = get_dr(2 * nod, st, m, c, v);
	if (x == (m - c + 1))
		return x + get_dr(2 * nod + 1, m + 1, dr, m + 1, v);
	return x;
}

int main() {
	time_t t = clock();
	int n, q;
	in >> n >> q;
	build_aint(1, 1, n);
	while (q--) {
		int t;
		in >> t;
		if (t == 1) {
			int a, b;
			in >> a >> b;
			aint_update(1, 1, n, a, b);

		} else {
			int x;
			in >> x;
			int v = get_val(1, 1, n, x);
 			int st = get_st(1, 1, n, x, v);
			int dr = get_dr(1, 1, n, x, v);
			out << v << ' ' << x - st + 1 << ' ' << x + dr - 1 << '\n';
		}
	}
	in.close();
	out.close();
	cerr << 1.0 * (clock() - t) / CLOCKS_PER_SEC << '\n';
    return 0;
}

