#include <iostream>
#include <vector>
using namespace std;

int t[2][2], s[2];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		t[x&1][y&1] = true;
		s[0] ^= x&1;
		s[1] ^= y&1;
	}
	if (s[0] == s[1]) {
		if (s[0] == 0)
			cout << 0;
		else
			if (t[1][0] || t[0][1])
				cout << 1;
	}
	else {
		cout << -1;
	}
	return 0;
}
