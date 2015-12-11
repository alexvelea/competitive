//Problem C from Codeforces Round facebookHackerCup2015Round1
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 4005, Mod = 1000000007;

int easy[kMaxN][kMaxN];

void add(int &a, int &b) {
	a += b;
	if (a >= Mod)
		a -= Mod;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	easy[1][1] = 1;
    for (int i = 1; i <= 4000; ++i) {
		for (int win = i / 2; win <= i; ++win) {
			if (i - win >= win) {
				easy[i][win] = 0;
			} else {
				add(easy[i + 1][win + 1], easy[i][win]);
				if ((i - win + 1) < win) {
					add(easy[i + 1][win], easy[i][win]);
				}
			}
		}
	}

    int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; ++T) {
		int a, b;
		scanf("%d-%d", &a, &b);
		assert(a <= 2000);
		assert(b <= 2000);

		printf("Case #%d: %d %d\n", T, easy[a + b][a], easy[b + b + 1][b + 1]);
	}
	return 0;
}
