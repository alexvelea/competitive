#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 2005;

#define ll long long

vector<ll> uniq;
int el[kMaxN], n, k;

int aint[2][8 * kMaxN], ind;

void aint_update(int nod, int st, int dr, int c, int val) {
	if (aint[ind][nod] < val)
		aint[ind][nod] = val;
	if (st == dr)
		return ;
	int m = (st + dr) / 2;
	if (c <= m)
		aint_update(2 * nod, st, m, c, val);
	else
		aint_update(2 * nod + 1, m + 1, dr, c, val);
	return ;
}

int aint_query(int nod, int st, int dr, int c1, int c2) {
	if (c1 <= st && dr <= c2)
		return aint[ind][nod];
	if (c2 < st || dr < c1)
		return 0;
	int m = (st + dr) / 2;
	return max(aint_query(2 * nod, st, m, c1, c2), aint_query(2 * nod + 1, m + 1, dr, c1, c2));
}

bool solve(ll x) {
	for (int i = 0; i < 8 * kMaxN; ++i) {
		aint[0][i] = 0;
		aint[1][i] = 0;
	}
	uniq.clear();

    for (int i = 1; i <= n; ++i) {
		uniq.push_back(1LL*(el[i] - (i - 1) * x));
		uniq.push_back(1LL*(el[i] + (i - 1) * x));
	}

 	uniq.push_back(- 1LL * n * 2 * inf);
	uniq.push_back(+ 1LL * n * 2 * inf);   

 	sort(uniq.begin(), uniq.end());
	uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
    cout << x << "|||||||||\n";
 	for (int i = 1; i <= n; ++i) {
		// avem elementul i
		ll st = 1LL * el[i] - n * x;
		ll dr = 1LL * el[i] + n * x;
		st = lower_bound(uniq.begin(), uniq.end(), st) - uniq.begin();
		dr = lower_bound(uniq.begin(), uniq.end(), dr) - uniq.begin();
		if (uniq[dr] != el[i] + x)
			--dr;
		cout << st << "%" << dr << "\n";
		ind = 0;
		int rez = aint_query(1, 1, 2 * n, st, n);
		ind = 1;
		rez = max(rez, aint_query(1, 1, 2 * n, 1, dr));
		rez ++;
		cout << rez << '\n';
		ind = 0;
		aint_update(1, 1, 2 * n, lower_bound(uniq.begin(), uniq.end(), 1LL * (el[i] - n * x)) - uniq.begin(), rez);
		ind = 1;
 		aint_update(1, 1, 2 * n, lower_bound(uniq.begin(), uniq.end(), 1LL * (el[i] - n * x)) - uniq.begin(), rez);   
		if (rez >= (n - k))
			return true;
	}
	return false;
}

int main() {
	freopen("date.in","r",stdin);
	cin >> n >> k;

	for (int i = 1; i <= n; ++i)
		cin >> el[i];

	ll rez = 0;
	ll p = 1LL * (1 << 0);
 	for (; p; p >>= 1) 
		if (solve(p + rez))
			;
		else
			rez += p;

	if (rez == 0 && solve(0)) {
		cout << '0';
	} else {
		cout << rez + 1;
	}
	return 0;
}
