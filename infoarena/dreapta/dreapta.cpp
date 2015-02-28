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

ifstream in("dreapta.in");
ofstream out("dreapta.out");

const int inf = 0x3f3f3f3f, kMaxN = 100005;

#define EPS 0.0000001

double x[kMaxN], y[kMaxN], xq[kMaxN], yq[kMaxN];
int rez[kMaxN];

vector<pair<double, int> > event;

bool my_sort(pair<double, int> a, pair<double, int> b) {
	if (EPS > a.first - b.first and -EPS < a.first - b.first)
		return a.second < b.second;
	return a.first < b.first;
}

bool inside(double Y, double a, double b) {
	if (a > b)
		swap(a, b);
	if (a <= Y and Y <= b)
		return true;
	return false;
}

int main() {
	int n, q;
	in >> n;
	for (int i = 0; i < n ; ++i)
		in >> x[i] >> y[i];
	x[n] = x[0];
	y[n] = y[0];
	in >> q;
	for (int i = 1; i <= q; ++i) {
		in >> xq[i] >> yq[i];
	}
	if (q == 1) {
		xq[2] = 10000.0;
	}
	double dx, dy, starty;
	dx = xq[1] - xq[2];
	dy = yq[1] - yq[2];
	dy /= dx;
	starty = yq[1] - xq[1] * (dy);
    for (int i = 0; i < n; ++i) {
		double Dx, Dy, StartY;
		Dx = x[i] - x[i + 1];
		Dy = y[i] - y[i + 1];
		Dy /= Dx;
		StartY = y[i] - x[i] * Dy;
		if (Dy - dy < EPS and Dy - dy > -EPS)
			continue;
		double X = (starty - StartY) / (Dy - dy);
		if (inside(X, x[i], x[i + 1])) {
			event.push_back(make_pair(X, 0));
		}
	}
	for (int i = 1; i <= q; ++i)
		event.push_back(make_pair(xq[i], i));
	sort(event.begin(), event.end(), my_sort);
    int inside = 0;
	for (int i = 0; i < int(event.size()); ++i) {
		if (event[i].second == 0)
			inside ^= 1;
		else
			rez[event[i].second] = inside;
	}
	for (int i = 1; i <= q; ++i)
		out << rez[i] << '\n';
	return 0;
}
