#include <algorithm>
#include <iostream>
using namespace std;

const int mod = 95542721, max_n = 100005;

int el[max_n], n;

struct arb {
	int lazy, sum[48];
} aint[4 * max_n];

void check (int &a) {
	while (a >= 48)
		a -= 48;
}

void next (int &a) {
	++a;
	check(a);
}

void make_sum (int nod) {
	for (int i = 0, st = aint[2 * nod].lazy, dr = aint[2 * nod + 1].lazy; i < 48; ++i, next(st), next(dr)) {
		aint[nod].sum[i] = aint[2 * nod].sum[st] + aint[2 * nod + 1].sum[dr];
		while (aint[nod].sum[i] >= mod)
			aint[nod].sum[i] -= mod;
	}
	return ;
}

void aint_init (int nod, int st, int dr) {
	if (st == dr) {
		aint[nod].sum[0] = el[st] % mod;
		for (int i = 1; i < 48; ++i) {
			aint[nod].sum[i] = (1LL * aint[nod].sum[i-1] * aint[nod].sum[i-1]) % mod;
			aint[nod].sum[i] = (1LL * aint[nod].sum[i] * aint[nod].sum[i-1]) % mod;
		}
		return ;
	}
	int m = (st + dr) / 2;
	aint_init (2 * nod, st, m);
	aint_init (2 * nod + 1, m + 1, dr);
	make_sum (nod);
}

void aint_update (int nod, int st, int dr, int a, int b) {
	if (b < st || dr < a)
		return ;
	if (a <= st && dr <= b) {
		aint[nod].lazy++;
		if (aint[nod].lazy == 48)
			aint[nod].lazy = 0;
		return ;
	}
	int m = (dr + st) / 2;
	aint_update (2 * nod, st, m, a, b);
	aint_update (2 * nod + 1, m + 1, dr,a ,b);
	make_sum (nod);
	return ;
}

int aint_query (int nod, int st, int dr, int a, int b, int lazy) {
	if (b < st || dr < a)
		return 0;
	lazy += aint[nod].lazy;
	check(lazy);
	if (a <= st && dr <= b)
		return aint[nod].sum[lazy];
	int rez = 0;
	int m = (st + dr) / 2;
 	rez += aint_query (2 * nod, st, m, a, b, lazy);
	rez += aint_query (2 * nod + 1, m + 1, dr, a, b, lazy);
	if (rez >= mod)
		rez -= mod;
	return rez;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	int q;
	cin >> q;
	aint_init (1, 1, n);
	while (q--) {
		int t, a, b;
		cin >> t >> a >> b;
		if (t == 1)
			cout << aint_query (1, 1, n, a, b, 0) << '\n';
		else
			aint_update (1, 1, n, a, b);
	}
	return 0;
}
