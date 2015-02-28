//Problem E from Codeforces Round 280
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

const int inf = 0x3f3f3f3f, kMaxN = 1000005;
int where[kMaxN], rez[kMaxN];

int main() {
	int n, m, dx, dy;
	cin >> n >> m >> dx >> dy;
	for (int l = 0, c = 0, i = 0; i < n; ++i) {
		where[c] = l;
		l += dx;
		c += dy;
		if (l >= n)
			l -= n;
		if (c >= n)
			c -= n;
	}

	for (int i = 1; i <= m; ++i) {
		int l, c;
		cin >> l >> c;
		l = l - where[c];
		if (l < 0)
			l += n;
		rez[l]++;
	}
	
	int mx = 0;
	for (int i = 0; i < n; ++i)
		if (rez[mx] < rez[i])
			mx = i;

	cout << mx << ' ' << 0 << '\n';
	return 0;
}
