#include <cmath>
#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

ifstream in("speculum.in");
ofstream out("speculum.out");

int64 sum[35];

map<pair< pair<int, int>, pair<int, pair<int, pair<int, int> > > > , int64> MP;

#define mp(a, b, c, d, e, f) (make_pair(make_pair(a, b), make_pair(c, make_pair(d, make_pair(e, f)))))

int ap;

int64 solve(int a, int b, int A, int B, int x, int y, int X, int Y, int p, bool inv) {
//	cerr << a << ' ' << b << ' ' << A << ' ' << B;
//	cerr << "\t\t" << x << ' ' << y << ' ' << X << ' ' << Y;
 	
	if (MP[mp(x - a, y - b, A - X, B - Y, p, inv)] != 0)
		return MP[mp(x - a, y - b, A - X, B - Y, p, inv)];
    ++ap;

	if (x == a and y == b and A == X and B == Y) {
//		cerr << "<-\t";
		if (inv) {
//			cerr <<  3LL * (1 << p) * (1 << p) - sum[p] << '\n';
			return 3LL * (1 << p) * (1 << p) - sum[p];
		}
//		cerr << sum[p] << '\n';
		return sum[p];
	}
	int64 rez = 0;
//	cerr << '\n';
	int am = (a + A) / 2;
	int bm = (b + B) / 2;
	int xn = x, yn = y, XN = X, YN = Y;
	
		xn = max(x, a);
		yn = max(y, b);
		XN = min(X, am);
		YN = min(Y, bm);

	if (xn <= XN and yn <= YN) {
		rez += solve(a, b, am, bm, xn, yn, XN, YN, p - 1, inv); 
	}
	
		xn = max(x, a);
		yn = max(y, bm + 1);
		XN = min(X, am);
		YN = min(Y, B);
 
 	if (xn <= XN and yn <= YN) {
		yn = bm + 1 + B - yn;
		YN = bm + 1 + B - YN;

		swap(yn, YN);
		
		rez += solve(a, bm + 1, am, B, xn, yn, XN, YN, p - 1, inv); 
	}

		xn = max(x, am + 1);
		yn = max(y, bm + 1);
		XN = min(X, A);
		YN = min(Y, B);
 
 	if (xn <= XN and yn <= YN) {
		// rotim coloanele
		yn = bm + 1 + B - yn;
		YN = bm + 1 + B - YN;
		swap(yn, YN);

		xn = am + 1 + A - xn;
		XN = am + 1 + A - XN;
		swap(xn, XN);
		
		rez += solve(am + 1, bm + 1, A, B, xn, yn, XN, YN, p - 1, inv);    	
	}

		xn = max(x, am + 1);
		yn = max(y, b);
		XN = min(X, A);
		YN = min(Y, bm);
 
 	if (xn <= XN and yn <= YN) {
		xn = am + 1 + A - xn;
		XN = am + 1 + A - XN;
		swap(xn, XN);
		
		rez += solve(am + 1, b, A, bm, xn, yn, XN, YN, p - 1, inv ^ 1);    	
 	}
	assert(x >= a);
	assert(y >= b);
	assert(A >= X);
	assert(B >= Y);
 	MP[mp(x - a, y - b, A - X, B - Y, p, inv)] = rez;
	return rez;
}

int main() {
	sum[0] = 1;
	for (int i = 1; i <= 30; ++i) {
		sum[i] = (2LL * sum[i - 1] + 3LL * (1 << (i - 1)) * (1 << (i - 1)));
	}
//	cerr << sum[1] << '\n';
//	cerr << sum[2] << '\n';
	int t;
	in >> t;
	while (t--) {
		int x, y, X, Y;
		in >> x >> y >> X >> Y;
//		out << solve(1, 1, 8, 8, x, y, X, Y, 3, 0) << '\n';
 		out << solve(1, 1, 1 << 30, 1 << 30, x, y, X, Y, 30, 0) << '\n';
	}
    return 0;
}
