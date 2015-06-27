//Problem prezenta from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 130, mod = 10007;

ifstream fin("prezenta.in");
ofstream fout("prezenta.out");

int dp[kMaxN][kMaxN][kMaxN];

int main() {
	dp[1][0][0] = 1;
	for (int n = 2; n < kMaxN; ++n) 
		for (int k = 0; k < kMaxN; ++k) {
			int up = 0;
			for (int last = 1; last < n; ++last) {
				up += dp[n - 1][k][last - 1];
				dp[n][k][last] += up;
				dp[n][k][last] %= mod;
			}
			int down = 0;
			for (int last = n - 2; last >= 0 and k; --last) {
				down += dp[n - 1][k - 1][last];
				dp[n][k][last] += down;
				dp[n][k][last] %= mod;
			}
		}
	
	int t; fin >> t;
	while (t--) {
		int n, k; fin >> n >> k;
		int rez = 0;
		for (int last = 0; last < n; ++last) {
			rez += dp[n][k][last];
		}
		fout << rez % mod << '\n';
	}
	return 0;
}
