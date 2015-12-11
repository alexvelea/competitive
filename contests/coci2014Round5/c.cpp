//Problem C from Codeforces Round coci.2014.round5
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

unordered_map<int, int> lin, col, d, d2;

int main() {
	int n, k;
    cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		lin[x]++;
		col[y]++;
		d[x - y]++;
		d2[x + y]++;
		if (lin[x] == k or col[y] == k or d[x - y] == k or d2[x + y] == k) {
			cout << i << '\n';
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
}
