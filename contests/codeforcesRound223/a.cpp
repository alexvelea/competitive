#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int kMaxN = 100005;

#define ll long long

ll sz[kMaxN];
pair<int, int> el[kMaxN];
int t[kMaxN], x[kMaxN], n, nr;

int bs(ll el) {
	int rez = 0;
	int p = 18;
	for (; p >= 0; --p) {
		if (rez + (1 << p) <= n and sz[rez + (1 << p)] <= el)
			rez += (1 << p);
	}
	return rez;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> t[i];
		sz[i] = 1LL * sz[i - 1];
		if (t[i] == 1) {
			cin >> el[i].first;
			sz[i]++;
			if (nr < kMaxN) { 
				x[++nr] = el[i].first;
			}
		} else {
			cin >> el[i].first >> el[i].second;
			sz[i] = sz[i] + 1LL * el[i].first * el[i].second;
			for (int c = 1; c <= el[i].second and nr < kMaxN; ++c)
				for (int l = 1; l <= el[i].first and nr < kMaxN; ++l)
                    x[++nr] = x[l];
		}
	}
	int m;
	cin >> m;

 	while (m--) {
   		ll p;
		cin >> p;
		if (p < kMaxN) {
			cout << x[p] << ' ';
			continue;
		}
 		int ind = bs(p);
		if (sz[ind] == p)
			--ind;
		++ind;
		if (t[ind] == 1) {
			cout << el[ind].first << ' ';
			continue;
		}

 		p -= sz[ind - 1];
		p %= el[ind].first;
		if (p == 0)
			p = el[ind].first;
		cout << x[p] << ' ';
	} 
	return 0;
}
