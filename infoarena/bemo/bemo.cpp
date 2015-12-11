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

ifstream in("bemo.in");
ofstream out("bemo.out");

const int inf = 0x3f3f3f3f, kMaxN = 1505;

pair<int, int> poz[kMaxN * kMaxN];
int rez[2 * kMaxN];

int n, m, aib[2 * kMaxN];

void aib_update(int ind, int el) {
	while (ind <= n + m) {
		aib[ind] += el;
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

int aib_search(int k) {
	if (k == 0)
		return 0;
	int rez = 0, p = 1 << 11;
	for (; p; p >>= 1)
		if (rez + p <= n + m) {
			if (aib[rez + p] < k) {
				k -= aib[rez + p];
				rez += p;
			}
		}
	return rez + 1;
}

int main() {
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int el;
			in >> el;
			poz[el] = make_pair(i, j);
		}
	in.close();
	aib_update(n + m, +1);
	rez[n + m] = n * m + 1;
	poz[n * m + 1] = make_pair(n + 1, m + 1);
	for (int i = 1; i <= n * m; ++i) {
 		int nr = poz[i].fi + poz[i].se - 1;
		if (rez[nr])
			continue;
		int sum = aib_query(nr);
		int st = aib_search(sum);
		int dr = aib_search(sum + 1);
		if (poz[rez[st]].fi <= poz[i].fi and poz[rez[st]].se <= poz[i].se and
			poz[rez[dr]].fi >= poz[i].fi and poz[rez[dr]].se >= poz[i].se) {
				rez[nr] = i;
				aib_update(nr, +1);
			}
	}
	for (int i = 1; i < n + m; ++i)
		out << rez[i] << ' ';
	out.close();
    return 0;
}
