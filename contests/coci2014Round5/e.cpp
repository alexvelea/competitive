//Problem E from Codeforces Round coci.2014.round5
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

const int inf = 0x3f3f3f3f, kMaxN = 505;

int close[kMaxN][kMaxN];
int Rez[kMaxN * kMaxN];
int n, m;

void insert(int l, int c) {
	close[l][c] = c;
	for (int C = c - 1; C; --C) {
		if (abs(close[l][C] - C) > abs(c - C) or close[l][C] == 0) {
			close[l][C] = c;
		} else {
			break;
		}
	}
	for (int C = c + 1; C <= m; ++C) {
 		if (abs(close[l][C] - C) > abs(c - C) or close[l][C] == 0) {
			close[l][C] = c;
		} else {
			break;
		}   	
	}
	return ;
}

int main() {
    cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char c;
			cin >> c;
			if (c == 'x') {
				insert(i, j);
			}
		}
	}
	int k;
	cin >> k;

	while (k--) {
 		int rez = 2 * kMaxN * kMaxN;
		int l, c;
		cin >> l >> c;
		for (int d = 0; d * d < rez; ++d) {
			if (l - d > 0) {
				if (close[l - d][c] != 0) {
					int cost = (d) * (d) + (close[l - d][c] - c) * (close[l - d][c] - c);
					if (cost < rez)
						rez = cost;
				}
			}
			if (l + d <= n) {
 				if (close[l + d][c] != 0) {
					int cost = (d) * (d) + (close[l + d][c] - c) * (close[l + d][c] - c);
					if (cost < rez)
						rez = cost;
				}   		
			}
		}
		insert(l, c);
		Rez[++Rez[0]] = rez;
	}
	for (int i = 1; i <= Rez[0]; ++i)
		cout << Rez[i] << '\n';

	return 0;
}
