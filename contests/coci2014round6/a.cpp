//Problem A from Codeforces Round coci2014round6
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
	int n, x; cin >> n >> x;
	vector<int> nr(n), choice(n);
	for (int i = 0; i < n; ++i) {
		cin >> nr[i] >> choice[i];
	}

	for (int i = 0; i + 1 < n; ++i) {
		if (nr[i] > nr[i + 1] and choice[i] == 1 and choice[i + 1] == 0) {
			swap(nr[i], nr[i + 1]);
		}
		if (nr[i] < nr[i + 1] and choice[i] == 0 and choice[i + 1] == 1) {
			swap(nr[i], nr[i + 1]);
		}
	}
	
	int rez = 0;
	for (int i = 0; i < n; ++i) {
		if (nr[i] > x and choice[i] == 0)
			++rez;
		if (nr[i] <= x and choice[i] == 1)
			++rez;
	}
	cout << rez << '\n';
	return 0;
}
