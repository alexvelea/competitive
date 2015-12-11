//Problem #E from Codeforces 229
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

const int inf = 0x3f3f3f3f, kMaxN = 4000005;

pair<int64, int64> aint[4 * kMaxN];

struct Event {
	int t, x1, x2, y, v;
	Event() {
		t = x1 = x2 = y = v = 0;
	}
	Event(int _t, int _x1, int _x2, int _y, int _v) {
		t = _t;
		x1 = _x1;
		x2 = _x2;
		y = _y;
		v = _v;
	}

	bool operator < (const Event &rhs) const {
		if (y == rhs.y) {
			if (t == 0)
				return 1;
			else
				return 0;
		}
		return y < rhs.y;
	}
};
vector<Event> e;

void aint_add(int nod, int x, int y, int &c1, int &c2, int64 &a, int64 &b) {
	if (y < c1 or c2 < x)
		return ;
	if (c1 <= x and y <= c2) {
		aint[nod].fi += a;
		aint[nod].se += b;
		return ;
	}

	int m = (x + y) / 2;
	aint_add(2 * nod, x, m, c1, c2, a, b);
	aint_add(2 * nod + 1, m + 1, y, c1, c2, a, b);
}

pair<int64, int64> aint_query(int nod, int x, int y, int &c1, int &c2) {
	if (y < c1 or c2 < x)
		return make_pair(0, 0);
	if (c1 <= x and y <= c2) {
		return make_pair(1LL * aint[nod].fi * (y - x + 1), 1LL * aint[nod].se * (y - x + 1));
	}
	int m = (x + y) / 2;
	pair<int64, int64> rez, a, b;
	a = aint_query(2 * nod, x, m, c1, c2);
	b = aint_query(2 * nod + 1, m + 1, y, c1, c2);
    rez.fi = aint[nod].fi * (min(c2, y) - max(c1, x) + 1);
	rez.se = aint[nod].se * (min(c2, y) - max(c1, x) + 1);
	rez.fi += a.fi;
	rez.fi += b.fi;
	rez.se += a.se;
	rez.se += b.se;
	return rez;
}

int64 rez[kMaxN];
bool ok[kMaxN];

int main() {
	int n, m, w;
	cin >> n >> m >> w;
	int64 now = 0;
	for (int i = 1; i <= w; ++i) {
		int t, x1, x2, y1, y2;
		cin >> t >> x1 >> y1 >> x2 >> y2;
		if (t == 0) {
			int v;
			cin >> v;
			now += 1LL * (x2 - x1 + 1) * (y2 - y1 + 1) * v;

            e.push_back(Event(0, x1, x2, y1, v));
			e.push_back(Event(0, x1, x2, y2 + 1, -v));
		} else {
			rez[i] -= now;
			ok[i] = true;
			e.push_back(Event(-i, 1, x2, y1 - 1, 0));
			e.push_back(Event(-i, 1, x1 - 1, y2, 0));
			e.push_back(Event(i, 1, x1 - 1, y1 - 1, 0));
			e.push_back(Event(i, 1, x2, y2, 0));
		}
	}
	cerr << now << '\n';
	sort(e.begin(), e.end());
	for (int i = 0; i < int(e.size()); ++i) {
		if (e[i].t == 0) {
			int64 a = - 1LL * (e[i].y - 1) * e[i].v;
			int64 b = e[i].v;
			cerr << e[i].y << '\t' << a << '\t' << b << "\t###\t" << e[i].x1 << '\t' << e[i].x2 << '\n';
        	aint_add(1, 1, n, e[i].x1, e[i].x2, a, b);
		} else {
        	pair<int, int> r = aint_query(1, 1, n, e[i].x1, e[i].x2);
			r.se *= 1LL * (e[i].y);
			if (e[i].t > 0) {
				rez[e[i].t] += 2 * (r.fi + r.se);
			} else {
				rez[-e[i].t] -= 2 * (r.fi + r.se);
			}
			cerr << '\t' << e[i].y << '\t' << e[i].x1 << '\t' << e[i].x2 << "\t######\t" << r.fi << '\t' << r.se << '\n';
		}
	}
	for (int i = 1; i <= w; ++i)
		if (ok[i])
			cout << rez[i] << '\n';
    return 0;
}

