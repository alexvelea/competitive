#include <iostream>
using namespace std;

const int max_n = 2005, mod = 1000000007;

int fact[max_n], inv_fact[max_n];
int el[max_n], inside[max_n];
int fre, target;

int pow (int a, int n) {
	int rez = 1;
	while (n) {
		if (n & 1)
			rez = (1LL * rez * a) % mod;
		a = (1LL * a * a) % mod;
		n >>= 1;
	}
	return rez;
}

int comb (int a, int b) {
	if (b > a)
		return comb(b, a);
	int rez = 1;
	rez = (1LL * rez * fact[a]) % mod;
	rez = (1LL * rez * inv_fact[b]) % mod;
	rez = (1LL * rez * inv_fact[a - b]) % mod;
	return rez;
}

int main() {
	int n = max_n - 1;
	fact[0] = 1;
 	for (int i = 1; i <= n; ++i)
		fact[i] = (1LL * fact[i - 1] * i) % mod;
	for (int i = 0; i <= n; ++i)
		inv_fact[i] = pow(fact[i], mod - 2);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		el[i] = x;
		inside[x] = true;
	}
	for (int i = 1; i <= n; ++i)
		if (el[i] == -1) {
			if (inside[i] == true)
				fre++;
			else
				target++;
		}
	int rez = fact[target + fre];
	for (int i = 1; i <= target; ++i) {
		int r = (1LL * comb(i, target) * fact[fre + target - i]) % mod;
		if (i & 1)
			rez -= r;
		else
			rez += r;
		while (rez < 0)
			rez += mod;
		rez %= mod;
	}
	cout << rez << '\n';
	return 0;
}
