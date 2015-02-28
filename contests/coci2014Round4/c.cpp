//Problem C from Codeforces Round coci.2014.round4
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 300005;

int64 el[kMaxN];

int main() {
	int n;
    cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	sort(el + 1, el + n + 1);
	int64 sum = 0;
	for (int i = 1; i < n; ++i)
		sum += 1LL * el[i];
	if (sum >= el[n])
		cout << sum + 1LL * el[n] << '\n';
	else
		cout << 2LL * el[n] << '\n';
	return 0;
}
