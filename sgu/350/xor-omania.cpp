#include <cmath>

#include <iostream>
#include <map>
using namespace std;

const int kMaxM = 105, kMaxN = 20;

map<int, bool> viz;
int el[kMaxM], x[kMaxN];

int main() {
	int m, n = 1;
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> el[i];
		viz[el[i]] = true;
	}
	x[1] = el[1];

	for (int i = 2; i <= m; ++i) {
		int oth = x[1] ^ el[i];
		if (viz[oth] == true) {
			viz[el[i]] = false;
			x[++n] = el[i];
		}
	}
 	for (int i = 3; i <= n; ++i) {
		if (viz[x[i] ^ x[2]] == false) {
			x[i] ^= x[1];
		}
	}

	cout << 0 << ' ';
	for (int i = 1; i <= n; ++i)
		cout << x[i] << ' ';
	return 0;
}
