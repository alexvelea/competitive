//Problem c from coci2014Round7
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 150005;

int min(int a, int b, int c) {
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	return a;
}

int dif[3][kMaxN], dp[3][8], oldDp[3][8];

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int p = 0; p < 3; ++p) {
		for (int i = 0; i < n; ++i) {
            cin >> dif[p][i];
		}
	}
	for (int i = 0; i < 8; ++i) {
		dp[0][i] = dp[1][i] = dp[2][i] = +inf;
	}
	
	for (int i = 0; i < 3; ++i) {
		dp[i][1 << i] = dif[i][0];
	}

    for (int i = 1; i < n; ++i) {
		for (int p = 0; p < 3; ++p) {
			for (int st = 0; st < 8; ++st) {
				oldDp[p][st] = dp[p][st];
			}
		}
 
 		for (int p = 0; p < 3; ++p) {
			for (int st = 0; st < 8; ++st) {
				if ((st & (1 << p)) == 0) {
					dp[p][st] = +inf;
				} else {
					dp[p][st] = min(oldDp[p][st], oldDp[(p + 1) % 3][st ^ (1 << p)], oldDp[(p + 2) % 3][st ^ (1 << p)]) + dif[p][i];
				}
			}
		}   	
	}
	cout << min(dp[0][7], dp[1][7], dp[2][7]);
	return 0;
}
