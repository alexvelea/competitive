#include <iostream>
using namespace std;

const int Mod = 1000000007;

int ap[32];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
   		cin >> n;
		for (int i = 0; i < 31; ++i)
			ap[i] = 0;
		for (int i = 1; i <= n; ++i) {
			int el;
			cin >> el;
			for (int j = 0; j < 31; ++j)
				if (el & (1 << j))
					ap[j] = true;
		}
		int sum = 0;
		int exp = 1;
		for (int i = 1; i < n; ++i) {
			exp *= 2;
			exp %= Mod;
		}

		int e = 1;
		for (int j = 0; j < 31; ++j) {
			if (ap[j])
				sum = (1LL * exp * e + sum) % Mod;
			e *= 2;
		}

		cout << sum << '\n';
	} 
	return 0;
}
