//Problem #C from Codeforces 230
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f, Mod = 1000000007;

map<int64, int> rez[41];
int comb[41][41];

int fibo(int64 n) {
	
}

int solve(int64 n, int k) {
	if (rez[k][n] != 0)
		return rez[k][n];
	if (n == 1)
		return 1;
	if (n == 2)
		return 1;
	if (n == 0)
		return 0;

	if (k == 1) {
		rez[k][n] = fibo(n + 2) - 1;
		if (rez[k][n] < 0)
			rez[k][n] += Mod;
		return rez[k][n];
	}
	int r = -pow(fibo(n), k);
	for (int i = 1; i < k; ++i) {
		r += (1LL * solve(n - 1, j) * comb[j][k]) % Mod;
		r %= Mod;
	}
	int d = 2;
	for (int i = k - 1; i > 0; --i) {
		r += (1LL * ((1LL * solve(n - 2, j) * comb[j][k]) % Mod) * d) % Mod;
		r %= Mod;
		d = (1LL * d * 2) % Mod;
	}
	r *= -1;
	r += Mod;
	r %= Mod;
	r += pow(fibo(n + 1), k);
	r %= Mod;
	rez[n][k] = r;
	return r;
}

int main() {
	int64 n;
	int k;
	for (int i = 0; i <= 40; ++i)
		comb[i][0] = 1;
	for (int i = 1; i <= 40; ++i)
		for (int j = 1; j <= i; ++j)
			comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % Mod;
 	cin >> n >> k;
	cout << solve(n, k);
    return 0;
}

