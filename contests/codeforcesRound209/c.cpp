#include <iostream>
#include <map>
using namespace std;

#define ll long long
const ll mod = 1000000007;

ll pow(ll a, ll p) {
	ll rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % mod;
		a = (1LL * a * a) % mod;
		p /= 2;
	}
	return rez;
}

ll min(ll a, ll b) {
	if (a < b)
		return a;
	return b;
}

map<int, int> ap;
ll el[100005];

int main() {
	int n;
	ll x;
	cin >> n >> x;
	ll s = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
		s += el[i];
	}
	ll mn = s;
	for (int i = 1; i <= n; ++i) {
		ap[s - el[i]] ++;
		if (s - el[i] < mn)
			mn = s - el[i];
	}
	while (1) {
		if (ap[mn] % x != 0)
			break;
		ap[mn + 1] += ap[mn] / x;
		++mn;
	}
	mn = min(mn, s);
	cout << pow(x, mn) << '\n';
}
