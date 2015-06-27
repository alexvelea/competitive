//Problem c from codeforcesLooksery
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

void D() {
	cout << "Daenerys\n";
	exit(0);
}

void S() {
	cout << "Stannis\n";
	exit(0);
}

int el[2];

int main() {
	ios::sync_with_stdio(false);
	int n, r, k; cin >> n >> r; k = n - r;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		el[x & 1]++;
	}

	if (k == 0) {
		if (el[1] % 2 == 1) {
			S();
		} else {
			D();
		}
	}

	if (k & 1) {
		// stannis are ultima mutare
		int d = k / 2;
		int s = k / 2 + 1;
		if (el[0] <= d) {
			if (r % 2 == 0) {
				D();
			}
		}
		
		if (el[0] <= s) {
			if (r % 2 == 1) {
				S();
			}
		}

		if (el[1] <= d) {
			D();
		}

		S();
	} else {
		// dany
 		int p = k / 2;
		if (el[1] <= p) {
			D();
		}
		if (el[0] <= p) {
			if (r % 2 == 1) {
				S();
			} else {
				D();
			}
		}
		D();
	}
	
	return 0;
}
