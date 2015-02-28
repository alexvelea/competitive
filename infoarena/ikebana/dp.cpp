#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

const int Mod = 666013;

int dp[90000][30][2];

ifstream in("ikebana.in");
ofstream out("ikebana.out");

int main() {
	int n, p, t;
	in >> n >> p >> t;

	dp[1][0][0] = 1;
	dp[1][p][1] = 2;
	dp[1][p][0] = t - 4;

	for (int i = 2; i <= n; ++i) {
 		dp[i][0][0] = dp[i - 1][p][0] + dp[i - 1][p][1];
		dp[i][0][0] %= Mod;
		dp[i][0][1] = 0;
		for (int j = 1; j <= p; ++j) {
			dp[i][j][0] += (t - 4) * (dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1]);
			dp[i][j][1] += 2 * (dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1]);
			dp[i][j][0] %= Mod;
			dp[i][j][1] %= Mod;
            if (i > 1 and j > 1) {
				dp[i][j][1] += dp[i - 2][j - 2][1];
 				dp[i][j][1] %= Mod;
			}
		}

 		dp[i][p][0] += (t - 4) * (dp[i - 1][p][0] + dp[i - 1][p][1]);
		dp[i][p][0] %= Mod;
		dp[i][p][1] += 2 * (dp[i- 1][p][0] + dp[i - 1][p][1]);
		dp[i][p][0] %= Mod;

		if (i > 1)
			dp[i][p][1] += dp[i - 2][p][1] + dp[i - 2][p - 1][1];
		dp[i][p][1] %= Mod;
	}
	int64 rez = 0;
	for (int i = 0; i <= p; ++i)
		rez += dp[n][i][0] + dp[n][i][1];
	out << rez % Mod << '\n';
	cerr << rez % Mod << '\n';
	return 0;
}
