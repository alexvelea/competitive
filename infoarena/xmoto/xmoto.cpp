#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("xmoto.in");

const int kMaxN = 50005;
const double eps = 0.000000001;

vector<double> rez;

struct Event{
	double a, b, k, q;
} event[kMaxN];

vector<pair<double, int> > Q;

int main() {
	double A = 0, K = 0;
	int n, l;
 	in >> n >> l;
	for (int i = 1; i <= n; ++i) {
		double v;
		in >> event[i].a >> event[i].b >> event[i].k >> event[i].q >> v;
		Q.push_back(make_pair(v, i));
		A += event[i].a;
		K += event[i].k;
	}
	Q.push_back(make_pair(10000.0, n + 1));
	++n;
	sort(Q.begin(), Q.end());
	double last = 0.0;
	for (int i = 0; i < n; ) {
		int st = i;
		double t = 1.0 * (l - K) / A;
		if (eps + last <= t and t <= Q[i].first + eps  and t <= 10000.0 + eps)
			rez.push_back(t);
		last = Q[i].first;
		while (i < n and fabs(Q[i].first - Q[st].first) <= eps) {
			A -= event[Q[i].second].a;
			A += event[Q[i].second].b;

			K -= event[Q[i].second].k;
			K += event[Q[i].second].q;

			++i;
        }
	}

    freopen("xmoto.out", "w", stdout);
	printf("%d\n", int(rez.size()));
	for (int i = 0; i < int(rez.size()); ++i)
		printf("%.8lf\n", rez[i]);
	return 0;
}
