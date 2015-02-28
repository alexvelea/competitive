#include <fstream>
#include <iostream>
using namespace std;

bool solve(int a, int b, int c, int d, int k) {
	int x[4] = {a, b, c, d};
	bool ok = true;
	for (int i = 0; i < 3; ++i) {
		x[i] %= k;
		if (x[i] > 1) {
			ok = false;
		}

		x[i + 1] += x[i];
	}
	if (x[3] % k != 0)
		ok = false;
	return ok;
}

int main() {
	int x, y, n;
	cin >> x >> y;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int k;
		cin >> k;
		if (solve(x, y - 1, x - 1, y - 2, k))
			cout << "YES\n";
		else
			if (solve(x - 1, y - 1, x - 1, y - 1, k))
				cout << "YES\n";
			else
				cout << "NO\n";
	}

	return 0;
}
