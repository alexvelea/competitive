//Problem B from Codeforces Round 280
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

int n, d, el[1005];

int main() {
    cin >> n >> d;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	sort(el + 1, el + n + 1);
	int rez = el[1];
	rez = max(rez, d - el[n]);
	rez *= 2;
	for (int i = 1; i < n; ++i)
		rez = max(rez, el[i + 1] - el[i]);
	cout << fixed << setprecision(9) << rez / 2.0 << '\n';
	return 0;
}
