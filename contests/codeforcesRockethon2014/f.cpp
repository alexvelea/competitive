//Problem #D from Codeforces rocket
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

const int inf = 0x3f3f3f3f;

#define int64 long long

int64 best[2][3005][3005];

void get_max(int64 &a, int64 b) {
	if (a < b)
		a = b;
}

int main() {
	int n, k;
 	cin >> n >> k;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= k + 1; ++j)
			best[0][i][j] = best[1][i][j] = -1LL * inf * inf;
	best[0][0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		int64 el;
		cin >> el;
		for (int j = 0; j <= k; ++j) {
			best[0][i][j] = best[0][i - 1][j];
			best[1][i][j] = best[1][i - 1][j];
			get_max(best[0][i][j], best[1][i - 1][j] + el);
			if (j > 0) 
				get_max(best[1][i][j], best[0][i - 1][j - 1] - el);
		}
	}
	int64 rez = -1LL*inf*inf;
	for (int j = 0; j <= k; ++j)
		get_max(rez, best[0][n][j]);
    cout << rez;
	return 0;
}

