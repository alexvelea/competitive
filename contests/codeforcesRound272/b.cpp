//Problem B from Codeforces Round 272
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int main() {
	string a, b;
	cin >> a >> b;
	int A = 0, B = 0, C = 0, n = int(a.size());
	for (int i = 0; i < n; ++i) {
		if (a[i] == '+')
			A++;
		else
			A--;
	}

	for (int i = 0; i < n; ++i) {
		if (b[i] == '+')
			B++;
		if (b[i] == '-')
			B--;
		if (b[i] == '?')
			C++;
	}

	int D = abs(A - B);

	if (D > C) {
		cout << "0.000000000000\n";
		return 0;
	}

	if (C == 0) {
		cout << "1.000000000000\n";
		return 0;
	}

	double rez = 1.0;

	int x = (C - D) / 2;
	int y = x + D;

	for (int i = 1; i <= C; ++i)
		rez *= 1.0 * i;
	for (int i = 1; i <= x; ++i)
		rez /= 1.0 * i;
	for (int i = 1; i <= y; ++i)
		rez /= 1.0 * i;
	for (int i = 1; i <= C; ++i)
		rez /= 2.0;
	cout << fixed << setprecision(9) << rez << '\n';

	return 0;
}
