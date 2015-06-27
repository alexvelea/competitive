//Problem c from mindcoding2015Finals1
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
 	int n, r; cin >> n >> r;
	cout << "(";
	for (int i = 1, N = n; i <= n and N > n / 4; ++i, N--) {
		cout << N;
		if (N - 1 != n / 4) {
			cout << "*";
		}
	}
	cout << "/(24^" << n / 4 << ")";
	cout << ")^" << r << '\n';
	return 0;
}
