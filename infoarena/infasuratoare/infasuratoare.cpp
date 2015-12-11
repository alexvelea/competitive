#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define int64 long long
#define x first
#define y second
#define Point pair<double, double>

ifstream in("infasuratoare.in");
ofstream out("infasuratoare.out");

const int kMaxN = 120005;
const double eps = 1e-12;

Point P[kMaxN], st[kMaxN];
int dr;

inline double CrossProduct (const Point &O, const Point &a, const Point &b) {
	return (a.x - O.x) * (b.y - O.y) - (a.y - O.y) * (b.x - O.x);
}

inline bool cmp(const Point &a, const Point &b) {
	return CrossProduct(P[1], a, b) > 0.0;
}

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> P[i].x >> P[i].y;
    int poz = 1;
	for (int i = 2; i <= n; ++i)
		if (P[i] < P[poz])
			poz = i;
	swap(P[1], P[poz]);
	sort(P + 2, P + n + 1, cmp);
//	for (int i = 1; i <= n; ++i)
//		out << P[i].x << '\t' << P[i].y << '\n';
	
	dr = 2;
	st[1] = P[1];
	st[2] = P[2];
	
	for (int i = 3; i <= n; ++i) {
		while (dr > 2 and CrossProduct(st[dr - 1], P[i], st[dr]) > 0.0)
			--dr;
		st[++dr] = P[i];
	}

	out << dr << '\n';
	for (int i = 1; i <= dr; ++i) {
		out << fixed << setprecision(12) << st[i].x << ' ' << st[i].y << '\n';
	}
	return 0;
}
