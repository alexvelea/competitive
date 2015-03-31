//Problem a from coci2014RoundFinal
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

struct Point {
	int64 x, y;

	Point() {
		x = y = 0;
	}
	Point(int64 _x, int64 _y) {
		x = _x;
		y = _y;
	}

  	int getC(int p) {
		int rez = 0;
		if (x & (1LL << p)) {
			rez = 2;
		}
		if (y & (1LL << p)) {
			rez += 1;
		}
		return rez;
	}
};

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> point[i].x >> point[i].y;
	}
	int p;
	int64 x = 0, y = 0;
	for (p = 31; p >= 0; --p) {
		bool viz[3] = {false, false, false};
		for (int i = 1; i <= n; ++i) {
			viz[point[i].getC(p)] = true;
		}
		int p = viz[0] + viz[1] + viz[2];
		if (p != 1) {
			// we have a winner
			if (viz[1] and viz[2]) {
				where = point(x, y);
			} else {
				
			}
		} else {
			x += (point[1].x & (1LL << p));
			y += (point[1].y & (1LL << p));
		}
	}
	return 0;
}
