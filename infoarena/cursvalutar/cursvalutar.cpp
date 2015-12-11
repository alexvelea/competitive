#include <cstdio>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

double max(double a, double b) {
	if (a > b)
		return a;
	return b;
}

double best[50][50];
double el[50][50];

int main() {
	freopen("cursvalutar.in", "r", stdin);
	freopen("cursvalutar.out", "w",stdout);
	int t;
	scanf("%d", &t);
	while (t--) {
		double s;
		int n, z;
		scanf("%lf %d %d", &s, &n, &z);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= z; ++j)
				scanf("%lf", &el[i][j]);

		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= z; ++j)
				best[i][j] = 0.0;
		best[0][0] = s;
		for (int i = 1; i <= z; ++i) {
			best[0][i] = best[0][i - 1];
			for (int j = 1; j <= n; ++j)
				best[0][i] = max(best[j][i - 1] * el[j][i], best[0][i]);
			for (int j = 1; j <= n; ++j)
				best[j][i] = max(1.0 * best[0][i] / el[j][i], best[j][i - 1]);
		}
		printf("%.9lf\n", best[0][z]);
	}
    return 0;
}
