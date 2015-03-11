#include <iostream>
using namespace std;

int dp[50][500][500];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		dp[1][i][i] = 1;
	}
	for (int j = 2; j <= k; ++j) {
		for (int sum = 1; sum <= n; ++sum) {
			for (int last = 1; last <= n; ++last) 
				for (int act = last + 1; act <= n; ++act) {
					dp[j][sum + act][act] += dp[j - 1][sum][last];
				}
		}
	}

	int rez = 0;
	for (int i = 1; i <= n; ++i)
		rez += dp[k][n][i];
	cout << rez << '\n';
	return 0;
}
