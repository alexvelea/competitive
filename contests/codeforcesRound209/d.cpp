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

struct interval{
	int min, gcd;
} aint[8 * max_n];

vector<int> ans;
int nr;

int n, el[max_n];

void make_aint(int nod, int st, int dr) {
	if (st == dr) {
		aint[nod].min = el[st];
		aint[nod].gcd = el[st];
		return ;
	}
	int m = (st + dr) / 2;
	make_aint(2 * nod, st, m);
	make_aint(2 * nod + 1, m + 1, dr);
	aint[nod].min = min(aint[2 * nod].min, aint[2 * nod + 1].min);
	aint[nod].gcd = gcd(aint[2 * nod].gcd, aint[2 * nod + 1].gcd);
	return ;
}

pair<int, int> query(int nod, int st, int dr, int c1, int c2) {
	if (c1 <= st && dr <= c2)
		return make_pair(aint[nod].min, aint[nod].gcd);
	if (dr < c1 || c2 < st)
		return make_pair(inf, 0);
	int m = (st + dr) / 2;
	pair<int, int> a, b, rez;
	a = query(2 * nod, st, m, c1, c2);
	b = query(2 * nod + 1, m + 1, dr, c1, c2);
	rez.first = min(a.first, b.first);
	rez.second = gcd(a.second, b.second);
	return rez;
}

bool solve(int l) {
	nr = 0;
	ans.clear();
	for (int i = 1; i + l <= n; ++i) {
		pair <int, int> q;
		q = query(1, 1, n, i, i + l);
		if (q.first == q.second) {
			nr ++;
			ans.push_back(i);
		}
	}
	if (nr)
		return true;
	return false;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
 	make_aint(1, 1, n);
	int p = (1 << 22);
	int rez = 0;
	for (; p; p /= 2)
		if (rez + p <= n)
			if (solve(rez + p))
				rez += p;
	solve(rez);
 	cout << nr << ' ' << rez << '\n';
	for (int i = 0; i < int(ans.size()); ++i)
		cout << ans[i] << ' ';
	return 0;
}
