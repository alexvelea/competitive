#include <fstream>
#include <cassert>
using namespace std;
int main() {
	int n = 50000, m = 100000;
	m = (((m - n + 1) / 3) * 3) + n - 1;
	assert(m >= n);
    ofstream cout("input.txt");

	cout << n << ' ' << m << '\n';
	for (int i = 1; i < n; ++i) {
		cout << 1 << ' ' << i << ' ' << i + 1 << '\n';
		--m;
	}
	while (m) {
		cout << 1 << ' ' << n - 1 << ' ' << n << '\n';
		cout << 3 << ' ' << 1 << ' ' << n << '\n';
		cout << 2 << ' ' << 1 << '\n';
		m -= 3;
	}
	cout.close();
	return 0;
}
