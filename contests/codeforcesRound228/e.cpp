#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define cx first.first
#define cy first.second

const int inf = 0x3f3f3f3f;
#define EPS 0.000000001

struct pct {
	double dx, dy, stx, sty;
	pair<double, double> check(double t) {
		return mp(stx + t * dx, sty + t * dy);
	}
	bool equal(pair<double, double> p, double t) {
		return ((abs(stx + dx * t - p.fi) < EPS) and ((abs(sty + dy * t - p.se)) < EPS));
	}
}point[1005];

vector<pair<pair<double, double>, double> > event;

bool mysort(pair< pair<double, double>, double> a, pair< pair<double, double>, double> b) {
	if ((abs(a.cx - b.cx) < EPS) and (abs(a.cy - b.cy) < EPS))
		return a.second < b.second;
	if (abs(a.cx - b.cx) < EPS)
		return a.cy < b.cy;
	return a.cx < b.cx;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		double t1,x1,x2,t2,y1,y2;
		cin >> t1 >> x1 >> y1 >> t2 >> x2 >> y2;
		point[i].dx = (x2 - x1) / (t2 - t1);
		point[i].dy = (y2 - y1) / (t2 - t1);
		point[i].stx = x1 - t1 * point[i].dx;
		point[i].sty = y1 - t1 * point[i].dy;
	}
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		event.clear();
		for (int j = 1; j <= n; ++j) {
	 		if (i == j)
				continue;
			if (abs(point[i].dx - point[j].dx) < EPS) {
				if (abs(point[i].dy - point[j].dy) < EPS)
					continue;
 				double t = (point[i].sty - point[j].sty) / (point[j].dy - point[i].dy);
				if (point[i].equal(point[j].check(t), t))
					event.push_back(make_pair(point[j].check(t), t));   	
			} else {
				double t = 1.0 * (point[i].stx - point[j].stx) / (point[j].dx - point[i].dx);
				cerr << i << '\t' << j << '\t' << t << '\n';
				if (point[i].equal(point[j].check(t), t))
					event.push_back(make_pair(point[j].check(t), t));
			}
		}
		sort(event.begin(), event.end(), mysort);
		for (int i = 0; i < int(event.size()); ) {
			int st = i, dr = i + 1;
			while (dr < int(event.size()) and (abs(event[st].cx - event[dr].cx) < EPS) and  (abs(event[st].cy - event[dr].cy) < EPS) and  (abs(event[st].second - event[dr].second) < EPS))
				++dr;
			if (mx < dr - st)
				mx = dr - st;
			i = dr;
		}
	}

	cout << mx + 1 << '\n';
	return 0;
}
