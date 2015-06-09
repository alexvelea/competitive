//Problem a from codeforcesRound299
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

int64 calc(int l, int a, int b) {
	return 1LL * a * l + 1LL * l * (l - 1) / 2 * b;
}

int main() {
	ios::sync_with_stdio(false);
	int a, b, n; cin >> a >> b >> n;
	while (n--) {
		int l, t, m; cin >> l >> t >> m;
 		int _dr = (t - a) / b + 1;
		int st = 1, dr = 1000000;
		while (st < dr) {
			int m = (st + dr) / 2;
			int64 r = 1LL * t * m - (calc(m, a, b) - calc(l - 1, a, b));
			cerr << m << '\t' << r << '\t' << calc(m, a, b) - calc(l - 1, a, b) << '\n';
			if (r >= 0) {
				dr = m;
			} else {
				st = m + 1;
			}
		}
		cerr << st << "!!\n";
		// st - 1
		_dr = min(_dr, st - 1);
		if (_dr < l) {
			cout << "-1\n";
		} else {
			cout << _dr << '\n';
		}
	}
	return 0;
}
