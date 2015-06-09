//Problem a from mindcodingFinalRound2
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
	if (n == 4) {
		cout << 2 << '\n';
		return 0;
	}

    for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			cout << "0\n";
            return 0;
		}
	}
	cout << n - 1 << '\n';
	return 0;
}
