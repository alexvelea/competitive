#include <iostream>
using namespace std;

const int max_n = 1000005, mod = 1000000007;

int el[max_n];
int aib[max_n], last[max_n];

void check (int &a) {
	while (a < 0)
		a += mod;
	while (a >= mod) 
		a -= mod;
}

int aib_query (int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
		check (rez);
	}
	return rez;
}
void aib_update (int ind, int val) {
	while (ind < max_n) {
		aib[ind] += val;
		check (aib[ind]);
		ind += ind & (-ind);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i < max_n; ++i)
		last[i] = -1;
	for (int i = 1; i <=n; ++i) {
		cin >> el[i];
		int q = aib_query (el[i]);
		int sum = q;
		sum ++;
		if (last[el[i]] != -1) {
			sum--;
			sum -= last[el[i]];
			check(sum);
		}
		last[el[i]] = q;
 		aib_update (el[i], (1LL * sum * el[i]) % mod);
	}
	cout << aib_query (max_n - 1);
	return 0;
}
