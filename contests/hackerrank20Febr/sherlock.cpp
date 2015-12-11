#include <iostream>
using namespace std;

const int kMaxN = 100005;
int el[2 * kMaxN];

int main() {
	int n, k, q;
	cin >> n >> k >> q;
	k %= n;
	for (int i = 0; i < n; ++i) {
		cin >> el[i];
		el[n + i] = el[i];
	}
	while (q--) {
		int poz;
		cin >> poz;
		cout << el[n + poz - k] << '\n';
	}
	return 0;
}
