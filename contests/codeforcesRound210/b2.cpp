#include <cstdio>
#include <iostream>
using namespace std;

#define ll long long

int n, best[2005], el[2005], k;

ll abs(ll a) {
	if (a < 0)
		return -a;
	return a;
}

bool solve(ll x) {
	for (int i = 1; i <= n; ++i)
		best[i] = 1;
	for (int i = 1; i <= n; ++i) { 
		for (int j = 1; j < i; ++j) {
			if (best[j] + 1 > best[i] && abs(el[i] - el[j]) <= 1LL * x * (i - j))
				best[i] = best[j] + 1;
		}
		if (best[i] >= (n - k))
			return true;
	}
	return false;
}

int main() {
	freopen("date.in","r",stdin);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
	}
	ll rez = 0, p = 1LL << 31;
	for (; p; p >>= 1LL)
		if (solve(rez + p))
			;
		else
			rez += p;
	if (solve(0)) {
		cout << '0';
	} else {
		cout << rez + 1;
	}
	return 0;
}
