#include <iostream>
using namespace std;

const int kMaxN = 105;

int el[kMaxN];
bool ok[kMaxN * kMaxN];

int main() {
    int t;
	cin >> t;
	while (t--) {
		int n, g, sum = 0;
		cin >> n >> g;
		for (int i = 1; i <= n; ++i) {
			cin >> el[i];
			sum += el[i];
		}
		if (sum > 2 * g) {
			cout << "NO\n";
			continue;
		}

		for (int i = 0; i <= sum; ++i)
			ok[i] = 0;
		ok[0] = 1;

		for (int i = 1; i <= n; ++i)
			for (int j = sum; j - el[i] >= 0; --j)
				if (ok[j - el[i]])
					ok[j] = true;

		int rez = 0;

		for (int i = min(sum, g); i; --i)
			if (ok[i]) {
				rez = i;
				break;
			}
		if (sum - rez <= g)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}
