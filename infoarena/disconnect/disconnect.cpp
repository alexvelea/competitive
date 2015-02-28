//Problem disconnect from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("disconnect.in");
ofstream out("disconnect.out");

int n, m;

bool viz[kMaxN];
int deep[kMaxN];

int rmq[kMaxN * 3][20], euler[3 * kMaxN], aib[3 * kMaxN];
int st[kMaxN], dr[kMaxN];

vector<int> vertex[kMaxN];

void aib_update(int ind, int v) {
	while (ind <= euler[0]) {
		aib[ind] += v;
		ind += ind & (-ind);
	}
}

int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}

void df(int nod) {
	euler[++euler[0]] = nod;
	st[nod] = euler[0];
	viz[nod] = true;

	for (int itr : vertex[nod]) {
		if (not viz[itr]) {
			deep[itr] = deep[nod] + 1;
			df(itr);
		 	euler[++euler[0]] = nod;   		
		}
	}
	euler[++euler[0]] = nod;
	dr[nod] = euler[0];
 	return ;
}

int lca(int a, int b) {
	a = st[a];
	b = st[b];
	if (a > b)
		swap(a, b);
	if (a == b)
		return euler[a];
	
	int p = 0;
	while (b - a + 1 > (1 << (p + 1)))
		++p;
	b -= (1 << p) - 1;
	if (deep[rmq[a][p]] < deep[rmq[b][p]])
		return rmq[a][p];
	else
		return rmq[b][p];
}

int query(int a, int b) {
	if (a == b)
		return 0;
	a = dr[a];
	b = dr[b];
	if (a > b)
		swap(a, b);
	b--;
	a--;
	return aib_query(b) - aib_query(a);
}

int main() {
	in >> n >> m;
	for (int i = 1; i < n; ++i) {
		int a, b;
        in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}
	df(1);
	for (int i = 1; i <= euler[0]; ++i)
		rmq[i][0] = euler[i];
	for (int p = 1; (1 << p) <= euler[0]; ++p) {
		for (int i = 1; i + (1 << p) - 1 <= euler[0]; ++i) {
			if (deep[rmq[i][p - 1]] < deep[rmq[i + (1 << (p - 1))][p - 1]])
				rmq[i][p] = rmq[i][p - 1];
			else
				rmq[i][p] = rmq[i + (1 << (p - 1))][p - 1];
		}
	}

	int v = 0;

	for (int i = 1; i <= m; ++i) {
		int t, x, y;
		in >> t >> x >> y;
		x ^= v;
		y ^= v;
		if (t == 1) {
			// remove
			if (deep[x] > deep[y])
				swap(x, y);
			aib_update(st[y], -1);
			aib_update(dr[y], +1);
		} else {
			int r = 0;
			int lc = lca(x, y);
			r += query(x, lc);
			r += query(y, lc);
			if (r != 0) {
				out << "NO\n";
				v = y;
			} else {
				out << "YES\n";
				v = x;
			}
		}
	}

	return 0;
}
