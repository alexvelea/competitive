//Problem #C from Codeforces MindCodingFinal2
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 100005;

double x[kMaxN], a[kMaxN], b[kMaxN], c[kMaxN], d[kMaxN];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}
    for (int i = 2; i <= n; ++i) {
		double r = -1.0 * a[i - 1] / b[i - 1];
		a[i - 1] = 0;
		b[i] += r * c[i - 1];
		d[i] += r * d[i - 1];
	}
	x[n] = d[n] / b[n];

    for (int i = n - 1; i >= 1; --i) {
		x[i] = (d[i] - c[i] * x[i + 1]) / b[i];
	}
	for (int i = 1; i <= n; ++i)
		printf("%.9lf\n", x[i]);
	return 0;
}

