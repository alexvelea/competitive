#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("euclid3.in");
ofstream out("euclid3.out");

int64 x, y;

int64 euclid(int64 a, int64 b) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}	

	int64 d = euclid(b, a % b);
	int64 cx = x;

	x = y;
	y = cx - y * (int64)(a / b);
	return d;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int64 a, b, c;
		in >> a >> b >> c;
		int64 d = euclid(a, b);

		if (c % d == 0) {
			out << x * c / d << ' ' << y * c / d << '\n';
		} else { 
			out << "0 0\n";
		}
	}
    return 0;
}
