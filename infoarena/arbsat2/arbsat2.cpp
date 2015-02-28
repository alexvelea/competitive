#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

ifstream in("arbsat2.in");
ofstream out("arbsat2.out");

const int INF = 0x3f3f3f3f, max_l = 100000;

vector<int> unic, x_coord[max_l + 5];
priority_queue <int> y_coord[max_l + 5];
int n, m;

struct point {
	int x, y;
	point (int _x, int _y) {
		x = _x;
		y = _y;
	}
	void make_small() {
		x = lower_bound(unic.begin(), unic.end(), x) - unic.begin();
		y = lower_bound(unic.begin(), unic.end(), y) - unic.begin();
	}
	void show() {
		out << x << ' ' << y << '\n';
	}
} ;
vector <point> pct, rez;

priority_queue <int> aint[5 * max_l];

void aint_update (int nod, int st, int dr, int poz, int val) {
	int m = (st + dr) / 2;
	if (val > 0)
		aint[nod].push(-val);
	else
		aint[nod].pop();
	if (st == dr)
		return;
	if (poz <= m)
		aint_update (2 * nod, st, m, poz, val);
	else
		aint_update (2 * nod + 1, m+1, dr, poz, val);
}

int aint_query (int nod, int st, int dr, int c1, int c2) {
	if (dr < c1 || c2 < st)
		return INF;
 	if (c1 <= st && dr <= c2) {
		if (aint[nod].size())
			return -aint[nod].top();
		return INF;
	}
	int m = (st + dr) / 2;
	int rez = INF;
	rez = min(rez, aint_query(2 * nod, st, m, c1, c2));
	rez = min(rez, aint_query(2 * nod + 1, m+1, dr, c1, c2));
	return rez;
}

void add_point (int x, int y) {
	x_coord[x].push_back(y);
	y_coord[y].push(-x);
	rez.push_back(point(unic[x], unic[y]));
	aint_update(1, 1, max_l, y, x);
	return ;
}

int main() {
	in >> n >> m;
	unic.push_back(-INF);
	for (int i = 1; i <= n; ++i) {
		int x, y;
		in >> x >> y;
		pct.push_back(point(x,y));
		unic.push_back(x);
		unic.push_back(y);
	}
	sort(unic.begin(), unic.end());
	unic.resize(unique(unic.begin(), unic.end()) - unic.begin());
	for (int i = 0; i < n; ++i)
		pct[i].make_small();
 	for (int i = 0; i < n; ++i) {
		x_coord[pct[i].x].push_back(pct[i].y);
		y_coord[pct[i].y].push(-pct[i].x);
		aint_update(1, 1, max_l, pct[i].y, pct[i].x);
	}	
	for (int i = 1; i <= max_l; ++i) {
		sort (x_coord[i].begin(), x_coord[i].end());
		for (int j = 0; j < int(x_coord[i].size()); ++j) {
			cerr << i << " " << x_coord[i][j] << "\n";
			y_coord[x_coord[i][j]].pop();
			aint_update(1, 1, max_l, x_coord[i][j], -i);
	    	int st, dr, top = INF;
			if (y_coord[x_coord[i][j]].size() != 0)
				top = -y_coord[x_coord[i][j]].top();
			if (j == 0)
				st = 0;
			else
				st = x_coord[i][j-1] + 1;
			if (j == int(x_coord[i].size()) - 1)
				dr = max_l;
			else
				dr = x_coord[i][j+1] - 1;
			int mn = INF;
//			cerr << st << "#" << dr << "\t" << top << "\n";
			if (st <= dr)
				mn = aint_query(1, 1, max_l, st, dr);
			if (mn < top && mn != INF)
				add_point(mn, x_coord[i][j]);
//			int x;
//			cin >> x;
		}
	}
	out << rez.size() << "\n";
	for (int i = 0; i < int(rez.size()); ++i)
		rez[i].show();
	return 0;
}

