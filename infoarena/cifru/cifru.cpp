#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define DEBUG 1
#define fi first
#define se second
#define int64 long long

ifstream in("cifru.in");
ofstream out("cifru.out");

const int inf = 0x3f3f3f3f, kMaxN = 2005, Mod = 19997;

int Fact[kMaxN], InvFact[kMaxN];
vector<int> el;
int dp[kMaxN];

int pow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (a * rez) % Mod;
		a = (a * a) % Mod;
		p >>= 1;
	}
	return rez;
}

int comb(int a, int b) {
	if (a < b)
		swap(a, b);
	int64 x = 1LL * Fact[a] * InvFact[b] * InvFact[a - b];
	return x % Mod;
}

int main() {
	int n, k;
	in >> n >> k;
	for (int d = 1; d * d <= k; ++d)
		if (k % d == 0) {
			el.push_back(d);
			if (d * d != k)
				el.push_back(k / d);
		}

	Fact[0] = Fact[1] = InvFact[0] = InvFact[1] = 1;
	for (int i = 2; i <= n; ++i) {
		Fact[i] = (1LL * i * Fact[i - 1]) % Mod;
		InvFact[i] = pow(Fact[i], Mod - 2);
	}

	dp[0] = 1;

	for (int i = 1; i <= n; ++i)
		for (int e : el) {
	 		if (i >= e) {
				dp[i] += dp[i - e] * ((Fact[e - 1] * comb(n - (i - e) - 1, e - 1)) % Mod);
				dp[i] %= Mod;
			}
		}
	out << dp[n];
    return 0;
}
