//Problem A from Codeforces Round 272
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

const int inf = 0x3f3f3f3f;

int main() {
	int n, m;
	cin >> n >> m;
 	int t = (n + 1) / 2;
	if (t % m != 0) {
		t -= t % m;
		t += m;
	}

	if (t <= n)
		cout << t << '\n';
	else
		cout << "-1\n";

	return 0;
}
