//Problem a from googleCodeJam2015Round1B
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream fin("data.in");
ofstream fout("data.out");

int border(int r, int c) {
	return 2 * (r + c) - 4;
}

int inside(int r, int c) {
	return r * c / 2 + (r * c) % 2;
}

void add(int x, int cost, int &n, int &ans) {
	x = min(n, x);
	n -= x;
	ans += cost * x;
}

int main() {
	ios::sync_with_stdio(false);
	int t; fin >> t;
	for (int i = 1; i <= t; ++i) {
		int r, c, n; fin >> r >> c >> n;
		if (r >= c) {
			swap(r, c);
		}
       
		int ans = 0;
		if (r == 1) {
			if ((c + 1) / 2 >= n) {
				ans = 0;
			} else {
				ans = (c - 1) - 2 * (c - n);
			}
		} else if (r == 2) {
			if (c >= n) {
				ans = 0;
			} else if (c + 2 >= n) {
				ans = 2 * (n - c);
			} else {
				ans = 3 * (n - c) - 2;
			}
		} else {
			ans = 0;

			add(inside(r, c), 0, n, ans);
			add(3 - (r % 2) - (c % 2) - (1 + r * c) % 2, 2, n, ans);
			add(border(r, c) + (r - 2) * (c - 2) / 2 - ((3 - (r % 2) - (c % 2) - (1 + r * c) % 2)) - inside(r, c), 3, n, ans);
			add(1000000000, 4, n, ans);
		}
		fout << "Case #" << i << ": " << ans << '\n';
	}
	return 0;
}
