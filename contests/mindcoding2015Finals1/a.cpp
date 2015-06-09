//Problem a from mindcoding2015Finals1
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	int64 rez = 1LL * n * (n + 1) / 2;
	if (rez % 2 == 1) {
		cout << 16 << '\n';
	} else {
		cout << 15 << '\n';
	}
	return 0;
}
