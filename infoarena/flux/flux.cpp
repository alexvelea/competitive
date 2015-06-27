//Problem flux from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 205;
const double eps = 0.000000001;

ifstream in("flux.in");
ofstream out("flux.out");

double gauss[kMaxN][kMaxN];
double rezN[kMaxN];

double min(double a, double b) {
	if (a > b)
		return b;
	return a;
}

bool equal(double a, double b) {
	if (-eps <= a - b and a - b <= eps)
		return true;
	return false;
}

vector<pair<int, int> > vertex[kMaxN];

int main() {
	int n, m; in >> n >> m;
	while (m--) {
		int a, b, c; in >> a >> b >> c;
		vertex[a].push_back(make_pair(b, c));
		vertex[b].push_back(make_pair(a, c));

		gauss[b][b] += 1.0;
		gauss[b][a] -= 1.0;

		gauss[a][a] += 1.0;
		gauss[a][b] -= 1.0;

		gauss[a][1] = gauss[b][1] = 0.0;
	}

	for (int l = 2; l < n; ++l) {
    	if (equal(gauss[l][l], 0.0))
			continue;
		double ratio = gauss[l][l];
		for (int c = 2; c <= n; ++c) {
			gauss[l][c] /= ratio;
		}
	}

	for (int l = 2; l < n; ++l) {
		if (vertex[l].size() == 0)
			continue;
//		assert(not equal(gauss[l][l], 0.0));

		for (int lp = 2; lp < n; ++lp) {
			if (lp == l)
				continue;
			if (not equal(gauss[lp][l], 0.0)) {
				double ratio = -1.0 * gauss[lp][l] / gauss[l][l];
				for (int c = 1; c <= n; ++c) {
					gauss[lp][c] += ratio * gauss[l][c];
				}
			}
		}
	}

	for (int i = 2; i <= n; ++i) {
		if (equal(gauss[i][i], 0.0)) {
			rezN[i] = 0.0;
		} else {
			rezN[i] = gauss[i][n] / gauss[i][i];
		}
		rezN[i] = fabs(rezN[i]);
//		cerr << i << '\t' << rezN[i] << '\n';
	}

	double flow = 0.0;
	for (auto itr : vertex[n]) {
		flow += 1.0;
		flow -= rezN[itr.first];
	}

	double mn = 1.0 * inf;

	for (int i = 2; i <= n; ++i) {
		for (auto itr : vertex[i]) {
			double current = fabs(rezN[i] - rezN[itr.first]);
			mn = min(mn, itr.second / current);
		}
	}

	out << fixed << setprecision(9) << mn * flow;
	return 0;
}
