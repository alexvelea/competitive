//Problem #A from Codeforces 236
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

int edge[50][50];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, p;
		cin >> n >> p;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				edge[i][j] = 0;
		for (int i = 2; i <= n; ++i)
			edge[1][i] = true;
		for (int i = 3; i <= n; ++i)
			edge[2][i] = true;
		edge[3][4] = edge[3][5] = edge[4][5] = true;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n and p; ++j)
				if (edge[i][j] == false) {
					edge[i][j] = true;
					p--;
				}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (edge[i][j])
					cout << i << ' ' << j << '\n';
	}
    return 0;
}

