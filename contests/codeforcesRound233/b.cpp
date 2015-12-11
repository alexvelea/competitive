//Problem #B from Codeforces 233
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

const int inf = 0x3f3f3f3f, kMaxN = 2005;

double rez[kMaxN][kMaxN];

bool viz_l[kMaxN], viz_c[kMaxN];

int main() {
	int n, m;
	cin >> n >> m;
    while (m--) {
		int l, c;
		cin >> l >> c;
		viz_l[l] = 1;
		viz_c[c] = 1;
	}
	int a = n, b = n;
	for (int i = 1; i <= n; ++i) {
		a -= viz_l[i];
		b -= viz_c[i];
	}

	rez[1][0] = rez[0][1] = 1.0 * n;

	for (int i = 0; i <= a; ++i)
		for (int j = 0; j <= b; ++j) {
        	if (i == 0 and j == 0)
				continue;
			if (i == 1 and j == 0)
				continue;
			if (i == 0 and j == 1)
				continue;

			double chx = 1.0 * (n - i) * (n - j) / n / n;
			double l = 1.0 * i * (n - j) / n / n;
			double c = 1.0 * (n - i) * j / n / n;
			double both = 1.0 * i * j / n / n;

 			rez[i][j] = ((rez[i - 1][j] * l + rez[i][j - 1] * c + rez[i - 1][j - 1] * both)) / (1 - chx);

		}
	cout << rez[a][b];
	return 0;
}

