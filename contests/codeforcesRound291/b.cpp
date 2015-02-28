//Problem B from Codeforces Round 291
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

map<pair<int, int>, bool> m;

int gcd(int a, int b) {
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	int n, x0, y0;
    cin >> n >> x0 >> y0;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		x -= x0;
		y -= y0;
		if (x < 0) {
			y *= -1;
			x *= -1;
		}
		if (x == 0) {
			y = abs(y);	
		}
 		int d = gcd(x, abs(y));
		x /= d;
		y /= d;
		m[make_pair(x, y)] = true;
	}
	cout << m.size() << '\n';
	return 0;
}
