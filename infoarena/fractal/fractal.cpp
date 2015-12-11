#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("fractal.in");
ofstream out("fractal.out");

int solve(int x, int y, int k) {
	if (k == 1) {
		if (x == 1 and y == 1)
			return 0;
		if (x == 1 and y == 2)
			return 3;
		if (x == 2 and y == 1)
			return 1;
		return 2;
	}
	k--;
	if (x <= (1 << k) and y <= (1 << k)) {
		swap(x, y);
		return solve(x, y, k);
	}
	if (y <= (1 << k)) {
		x -= 1 << k;
		return (1 << (2 * k)) + solve(x, y, k);
	}
	if (x <= (1 << k)) {
        y -= (1 << k);
		swap(x, y);
		x = (1 << k) - x + 1;
		y = (1 << k) - y + 1;
		return 3 * (1 << (2 * k)) + solve(x, y, k);
	}

	x -= (1 << k);
	y -= (1 << k);
	return 2 * (1 << (2 * k)) + solve(x, y, k);
}

int main() {
	int x, y, k;
	in >> k >> y  >> x;
	assert(x <= (1 << k));
	assert(y <= (1 << k));
	out << solve(x, y, k);
    return 0;
}
