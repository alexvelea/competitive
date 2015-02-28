#include <cassert>

#include <iostream>
using namespace std;

const int kMaxN = 205, inf = 0x3f3f3f3f;

int cost[kMaxN][kMaxN], el[kMaxN][kMaxN];
int n, m;


void get_min(int &a, int b) {
	if (a > b)
		a = b;
}

bool solve(int st, int dr) {
 	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			cost[i][j] = inf;
 			if (st <= el[i][j] and el[i][j] <= dr)
				cost[i][j] = 1;
		}
	for (int i = 1; i <= n; ++i)
		cost[i][i] = 0;

	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				get_min(cost[i][j], cost[i][k] + cost[k][j]);
			}
  	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (cost[i][j] > 3)
				return false;
	return true;
}

int main() {
	cin >> n >> m;
 //   assert(m);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j)
			cin >> el[i][j];
	if (n == 1) {
		cerr << "0";
		return 0;
	}
	if (m == 0) {
		cerr << "-1";
		return 0;
	}
	cerr << '\n';
	if (solve(1, (m + 1) / 2)) {
		cout << (m + 1) / 2 << '\n';
		for (int i = 1; i <= (m + 1) / 2; ++i)
			cout << i << ' ';
	} else {
		cout << (m + 1) / 2 << '\n';
		for (int i = m - (m + 1) / 2 + 1; i <= m; ++i)
			cout << i << ' ';
	}
	return 0;
}
