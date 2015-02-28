//Problem E from Codeforces Round rockethon2015
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

const int inf = 0x3f3f3f3f;

int sum[500];
int dp[55][555][555];

int main() {
	int n, K;
    cin >> n >> K;
	for (int i = 1; i <= n; ++i) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}

	int mx = 0;

	for (int k = 2; k <= K; ++k) {
		int mx0 = -inf;
		int mx1 = -inf;

		for (int st = 1; st <= n; ++st) {
			for (int dr = st; dr <= n; ++dr) {
				dp[k][st][dr] = sum[dr] - sum[st - 1] + mx0;
				dp[k][st][dr] = max(dp[k][st][dr], - (sum[dr] - sum[st - 1]) + mx1);
				if (dp[k][st][dr] > mx and k == K)
					mx = dp[k][st][dr];
			}
			for (int x = 1; x <= st; ++x) {
				mx0 = max(mx0, dp[k - 1][x][st] - (sum[st] - sum[x - 1]));
				mx1 = max(mx1, dp[k - 1][x][st] + (sum[st] - sum[x - 1]));
			}
		}
	}
	cout << mx << '\n';
	return 0;
}
