#include <iostream>
using namespace std;

#define ll long long

int main() {
	ll n;
	cin >> n;
	if (n == 1) {
		cout << "0\n";
		return 0;
	}
 	for (int i = 1; ; ++i) {
		ll s = i;
		for (int j = 1; j <= 1 + i and s < n; ++j) 
			s += s + 1;
		if (s >= n) {
			cout << i << '\n';
			return 0;
		}
	}
	return 0;
}
