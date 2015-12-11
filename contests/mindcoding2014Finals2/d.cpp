//Problem #D from Codeforces MindCodingFinal2
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

double a, a2, b, b2, A, B;

int x[105], y[105];
int n;

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
    	cin >> x[i] >> y[i];
		a += -2LL * x[i] * y[i];
		b += - 2LL * y[i];
		a2 += 1LL * x[i] * x[i];
		b2 += 1;
	}
	A = 1.0 * - a / (2LL * a2);
	B = 1.0 * - b / (2LL * b2);
	double rez = 0.0;
	for (int i = 1; i <= n; ++i) {
		rez += (y[i] - (A * x[i] + B)) * (y[i] - (A * x[i] + B));
	}
	printf("%.6lf", rez);
    return 0;
}

