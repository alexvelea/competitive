#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second

int main() {
	int n, el, nr_r = 0;
	long long rez;
 	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> el;
		if (el == 1) {
			++nr_r;
		} else {
			rez = rez + 1LL * nr_r;
		}
	}
	cout << rez << '\n';
}
