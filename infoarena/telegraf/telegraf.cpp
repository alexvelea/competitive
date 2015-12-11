#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("telegraf.in");
ofstream out("telegraf.out");
const int inf = 0x3fdfdfdf;

int sum[40], cost[40];
int dp[40][80][80]; // [la_ce_chestie is][cate is de +0][cate is de +1]

void get_min(int &a, int b) {
	if (a > b)
		a = b;
}

int main() {
	for (int i = 0; i < 36; ++i) {
		int x;
		in >> x;
		cost[i] = x;
	}
	sort(cost + 0, cost + 36);
	reverse(cost + 0, cost + 36);
	for (int i = 1; i <= 36; ++i)
		sum[i] = sum[i - 1] + cost[i - 1];
	for (int a = 0; a < 40; ++a)
		for (int b = 0; b < 80; ++b)
			for (int c = 0; c < 80; ++c)
				dp[a][b][c] = inf;
	int m = 0;
	for (m = 0; cost[m] != 0; ++m)
		;
	dp[0][1][0] = 0;
	for (int n = 0; n < m; ++n)
		for (int a = 0; n + a <= m; ++a)
			for (int b = a; b < 80; ++b)
				for (int c = 0; (b - a) + c < 80; ++c)
					get_min(dp[n + a][(b - a) + c][b - a], dp[n][b][c] + sum[36] - sum[n + a]);
	int mn = inf;
	for (int b = 0; b < 80; ++b)
		for (int c = 0; c < 80; ++c)
			if (dp[m][b][c] < mn)
				mn = dp[m][b][c];
	out << mn << '\n';
	return 0;                       
}
