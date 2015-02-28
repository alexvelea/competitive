//Problem C from Codeforces Round memsql
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

const int inf = 0x3f3f3f3f;

int main() {
	int n, m;
	long double rez = 0;
//	cin >> n >> m;
	n = 1000;
	m = 1000;
	for (int i = 1; i <= min(n, m); ++i) {
		long double rez2 = 1.0;
		for (int j = 1; j <= i; ++j) {
			rez2 *= 1.0 * (m - j + 1) / (n * m - j + 1);
		}
		for (int j = i + 1; j <= n; ++j) {
			rez2 *= 1.0 * ((n - 1) * m - j + i + 1) / (n * m - j + 1);
		}
		for (int j = 1; j <= n; ++j)
			rez2 *= 1.0 * j;
		for (int j = 1; j <= i; ++j)
			rez2 /= 1.0 * j;
		for (int j = 1; j <= n - i; ++j)
			rez2 /= 1.0 * j;
		rez2 *= 1.0 * i * i / n / n;
		rez += rez2;
	}
	rez *= n;
	cout << fixed << setprecision(10) << rez << '\n';
	return 0;
}
