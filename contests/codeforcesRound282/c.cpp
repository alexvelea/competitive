//Problem C from Codeforces Round 282
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

double el[kMaxN], sum[kMaxN];

int main() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];

	}
	for (int i = 1; i <= q; ++i) {
		int a, b;
		double c;
		cin >> a >> b >> c;
		sum[a] += c;
		sum[b + 1] -= c;
	}
 	for (int i = 1; i <= n; ++i)
		sum[i] += sum[i - 1];
	double mx = 0;
	for (int i = 1; i <= n; ++i) {
		cerr << sum[i] << '\n';
		if (mx < sum[i] + el[i])
			mx = sum[i] + el[i];
	}
	cout << fixed << setprecision(4) << mx << '\n';
	return 0;
}
