//Problem C from Codeforces Round 286
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int here[30005], best[30005][605];

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int n, d;
    cin >> n >> d;
	for (int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		here[a]++;
	}
	int mx = 0;
	best[d][300 ] = here[0] + 1;
	for (int l = 0; l <= 30000; ++l) {
		for (int D = 1; D < 600; ++D) {
			if (best[l][D] == 0)
				continue;

			best[l][D] += here[l];
			int dx = d + D - 300;
			if (dx <= 0)
				continue;
			getMax(mx, best[l][D]);
 			if (dx + l <= 30000) {
				getMax(best[l + dx - 1][D - 1], best[l][D]);
				getMax(best[l + dx][D], best[l][D]);
				getMax(best[l + dx + 1][D + 1], best[l][D]);
			}
		}
	}
	cout << mx - 1 << '\n';
	return 0;
}
