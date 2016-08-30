//Problem c @ 30-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 505;

#define int64 long long

char el[kMaxN][kMaxN];

int Left[kMaxN][kMaxN], Down[kMaxN][kMaxN];
int sumLeft[kMaxN][kMaxN], sumDown[kMaxN][kMaxN];

int sum(int x1, int y1, int x2, int y2, int S[kMaxN][kMaxN]) {
	return S[x2][y2] - S[x2][y1 - 1] - S[x1 - 1][y2] + S[x1 - 1][y1 - 1];
}

int main() {
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			cin >> el[i][j];
		}
	}

	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			if (el[i][j] != '.') {
				continue;
			}

			if (el[i - 1][j] == '.') {
				Down[i][j] += 1;
			}
			if (el[i][j - 1] == '.') {
				Left[i][j] += 1;
			}
		}
	}

	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			sumDown[i][j] = sumDown[i - 1][j] + sumDown[i][j - 1] - sumDown[i - 1][j - 1] + Down[i][j];
			sumLeft[i][j] = sumLeft[i - 1][j] + sumLeft[i][j - 1] - sumLeft[i - 1][j - 1] + Left[i][j];
		}
	}

	int q; cin >> q;
	while (q--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		int rez = 0;
		if (x1 < x2) {
			x1 += 1;
			rez += sum(x1, y1, x2, y2, sumDown);
			// cerr << rez << '\n';
			x1 -= 1;
		}

		if (y1 < y2) {
			y1 += 1;
			rez += sum(x1, y1, x2, y2, sumLeft);
			// cerr << rez << '\n';
			y1 -= 1;
		}

		cout << rez << '\n';
	}

	return 0;
}
