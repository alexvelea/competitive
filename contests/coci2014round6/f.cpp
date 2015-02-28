#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int a[3005];
int from[3005][3005], dp[3005][3005];

int main() {
	int n, r; cin >> n >> r;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 2; i <= n + 1; ++i) {
		vector<int> up(n + 2), fromUp(n + 2);
		up[n - 1] = -a[n] + dp[i - 1][n - 1];
		fromUp[n - 1] = n - 1;
    	for (int j = n - 2; j >= 1; --j) {
			if (up[j + 1] > -a[j + 1] + dp[i - 1][j]) {
				up[j] = up[j + 1];
				fromUp[j] = fromUp[j + 1];
			} else {
				up[j] = -a[j + 1] + dp[i - 1][j];
				fromUp[j] = j;
			}
		}
 		int down = a[1] + dp[i - 1][1], fromDown = 1;
		for (int j = 1; j < n; ++j) {
			if (down < a[j] + dp[i - 1][j]) {
				fromDown = j;
				down = a[j] + dp[i - 1][j];
			}
			dp[i][j] = a[j] + up[j];
			from[i][j] = fromUp[j];
			if ((down - a[j + 1]) > dp[i][j]) {
				dp[i][j] = down - a[j + 1];
				from[i][j] = fromDown;
			}
		}

		rotate(a + 1, (a + 1) + n - r, a + n + 1);
	}
	int mx = dp[n][1], fromMx = 1;
	for (int i = 1; i < n; ++i) {
		if (mx < dp[n + 1][i]) {
			mx = dp[n + 1][i];
			fromMx = i;
		}
	}
	vector<int> rez;
	rez.reserve(n + 5);
	for (int l = n + 1; l; --l) {
		rez.push_back(fromMx);
		fromMx = from[l][fromMx];
	}
	reverse(rez.begin(), rez.end());
	cout << mx << '\n';
	for (auto itr : rez) {
		cout << itr << ' ';
	}
	return 0;
}
