//Problem #B from Codeforces 237
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f;

void show(int64 l, int A) {
	if (l <= 1LL * A) {
		printf("%.5lf 0.00000\n", l / 10000.0);
		return ;
	}
	if (l <= 2LL * A) {
		l -= A;
		printf("%.5lf %.5lf\n", A / 10000.0, l / 10000.0);
		return ;
	}
	if (l <= 3LL * A) {
		l -= 2LL * A;
		l = A - l;
		printf("%.5lf %.5lf\n", l / 10000.0, A / 10000.0);
		return ;
	}
	l -= 3LL * A;
	l = A - l;
	printf("0.00000 %.5lf\n", l / 10000.0);
}

int main() {
	double a, d;
	int n;

	cin >> a >> d;
	cin >> n;

	int A = int(a * 10000.0 + 0.5);
	int D = int(d * 10000.0 + 0.5);

	int64 l = 0;

 	for (int i = 1; i <= n; ++i) {
		l += 1LL * D;
		l %= (1LL * 4 * A);
		show(l, A);
	}
    return 0;
}

