//Problem c from mindcodingRound4
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMod = 666013;

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	int rez = 0;
	int m = 1;

	m = 1;
	for (int i = 1; i <= 2 * n; ++i) {
		m = (1LL * m * (2 * n - i + 1)) % kMod;
		rez = (rez + m) % kMod;
	}
	m = 2;
	for (int i = 1; i <= n; ++i) {
		m = (1LL * m * (n - i + 1)) % kMod;
		rez -= m;
		if (rez < 0)
			rez += kMod;
	}

	cout << rez << '\n';
	return 0;
}
