#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int max_n = 3 * 100005, inf = 0x3f3f3f3f;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int aint[8 * max_n];

int st[max_n], dr[max_n];

vector<int> rez;
int ans[max_n], mx = 0;

int n, el[max_n];

int nr, stck[max_n];

void make_aint(int nod, int st, int dr) {
	if (st == dr) {
		aint[nod] = el[st];
		return ;
	}
	int m = (st + dr) / 2;
	make_aint(2 * nod, st, m);
	make_aint(2 * nod + 1, m + 1, dr);
	aint[nod] = gcd(aint[2 * nod], aint[2 * nod + 1]);
	return ;
}

int query(int nod, int st, int dr, int c1, int c2) {
	if (c1 <= st && dr <= c2)
		return aint[nod];
	if (dr < c1 || c2 < st)
		return 0;
	int m = (st + dr) / 2;
	int a, b;
	a = query(2 * nod, st, m, c1, c2);
	b = query(2 * nod + 1, m + 1, dr, c1, c2);
	return gcd(a, b);
}

void solve(int ind) {
	if (el[ind] == el[ind - 1])
		return ;
	// stanga
	int p = (1 << 22);
	int rez = 0;
	int cst, cdr;
	for (; p; p /= 2)
		if (ind - p - rez >= 1 && st[ind] <= ind - p - rez)
			if (query(1, 1, n, ind - p - rez, ind) == el[ind])
				rez += p;
	cst = ind - rez;
	p = (1 << 22);
	rez = 0;
	for (; p; p /= 2)
		if (ind + p + rez <= n && dr[ind] >= ind + p + rez)
			if (query(1, 1, n, ind, ind + p + rez) == el[ind])
				rez += p;
	cdr = ind + rez;
	if (ans[cst] < cdr - cst)
		ans[cst] = cdr - cst;
}

int main() {
	cin >> n;
	int g = -1;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
		if (g == -1)
			g = el[i];
		g = gcd(g, el[i]);
	}
	for (int i = 1; i <= n; ++i) {
		el[i] /= g;
		if (el[i] == 1) {
			cout << 1 << ' ' << n - 1 << '\n' << 1 << '\n';
			return 0;
		}
	}
 	make_aint(1, 1, n);

    nr = 0;
	for (int i = 1; i <= n; ++i) {
		while (nr && el[stck[nr]] > el[i]) {
			dr[stck[nr]] = i;
			--nr;
		}
		stck[++nr] = i;
	}
	for (int i = 1; i <= nr; ++i)
		dr[stck[i]] = n + 1;
	nr = 0;
	for (int i = n; i; --i) {
		while (nr && el[stck[nr]] > el[i]) {
			st[stck[nr]] = i;
			--nr;
		}
		stck[++nr] = i;
	}
	for (int i = 1; i <= nr; ++i)
		st[stck[i]] = 0;

/*	for (int i = 1; i <= n; ++i)
		cerr << st[i] << ' ';
	cerr << '\n';
	for (int i = 1; i <= n; ++i)
		cerr << dr[i] << ' ';
	cerr << '\n';*/


	for (int i = 1; i <= n; ++i)
		solve(i);
	for (int i = 1; i <= n; ++i) {
		if (mx < ans[i]) {
			rez.clear();
			mx = ans[i];
		}
		if (mx == ans[i])
			rez.push_back(i);
	}
	cout << rez.size() << ' ' << mx << '\n';
	for (int i = 0; i < int(rez.size()); ++i)
		cout << rez[i] << ' ';
	return 0;

}
