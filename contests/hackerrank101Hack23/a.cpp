//Problem a from hackerrank101Hack23
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
 	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		bool alive = true, changesLeft = true;
		int sum = 0, mn = 0;

		for (int i = 1; i <= n; ++i) {
			int x; cin >> x;
			sum += x;
			mn = min(mn, x);
			if (sum < 0 and changesLeft == false) {
				cout << i << '\n';
				alive = false;
				++i;
				while (i <= n) {
					cin >> x;
					i++;
				}
				break;
			}

			if (sum < 0) {
				sum += -2 * mn;
				changesLeft = false;
			}
		}

		if (alive) {
			cout << "She did it!\n";
		}
	}
	return 0;
}
