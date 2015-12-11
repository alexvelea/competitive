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

ifstream in("biscuiti.in");
ofstream out("biscuiti.out");

const int inf = 0x3f3f3f3f, kMaxN = 100005;

struct AintNode {
	int64 min, lazy;
} aint[4 * kMaxN];

int el[kMaxN];

void aint_init(int nod, int st, int dr) {
	if (st == dr) {
    	aint[nod].min = el[st];
		return ;
	}
	int m = (st + dr) / 2;
	aint_init(2 * nod, st, m);
	aint_init(2 * nod + 1, m + 1, dr);
	aint[nod].min = min(aint[2 * nod].min, aint[2 * nod + 1].min);
	return ;
}

pair<int64, int> aint_query(int nod, int st, int dr) {
	if (st == dr) {
		return make_pair(aint[nod].min, st);
	}
	int m = (st + dr) / 2;
	pair<int64, int> rez;
	if (aint[2 * nod].min <= aint[2 * nod + 1].min)
		rez = aint_query(2 * nod, st, m);
	else
		rez = aint_query(2 * nod + 1, m + 1, dr);
 	rez.first += aint[nod].lazy;
	return rez;   
}

void aint_update(int nod, int st, int dr, int c, int val) {
	if (dr < c) {
		aint[nod].lazy += 1LL * val;
		aint[nod].min += 1LL * val;
		return ;
	}

	if (st == dr and dr == c) {
		aint[nod].min = 1LL * inf * inf;
		return ;
	}

	if (st > c)
		return ;

	int m = (st + dr) / 2;
	aint_update(2 * nod, st, m, c, val);
	aint_update(2 * nod + 1, m + 1, dr, c, val);

	aint[nod].min = min(aint[2 * nod].min, aint[2 * nod + 1].min);
	aint[nod].min += aint[nod].lazy;
	return ;
}

int main() {
	int n;
	int64 fin = 0;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
		fin -= el[i];
	}
	aint_init(1, 1, n);

	for (int i = 1; i <= n; ++i) {
		pair<int64, int> rez = aint_query(1, 1, n);
//		cerr << rez.first << '\t' << rez.second << '\n';
		aint_update(1, 1, n, rez.second, +i);
		fin += rez.first;
	}
	out << fin << '\n';
    return 0;
}
