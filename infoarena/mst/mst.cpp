#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("mst.in");
//ofstream out("mst.out");

const int kMaxN = 105;

vector<double> events;
double t;
int n, m;

struct Edge {
	int x, y;
	double a, b, c;

	pair<double, double> cross(Edge rhs) {
		double A = a - rhs.a;
		double B = b - rhs.b;
		double C = c - rhs.c;

		if (A == 0 and B == 0) {
			return make_pair(0, 0);
		}
		if (A == 0) {
			return make_pair(0, - C / B);
		}

		double delta = B * B - 4 * A * C;
		
		if (delta < 0)
			return make_pair(0, 0);

		double r1, r2;
		delta = sqrt(delta);
		r1 = (-B + delta) / 2.0 / A;
		r2 = (-B - delta) / 2.0 / A;

		return make_pair(r1, r2);
	}

	bool operator < (const Edge &rhs) const {
		return a * t * t + b * t + c < 1.0 * rhs.a * t * t + rhs.b * t + rhs.c;
	}
} edge[kMaxN];

double A, B, C;

int father[kMaxN];

int get_father(int a) {
	if (father[a] == a)
		;
	else
		father[a] = get_father(father[a]);
	return father[a];
}

bool unite(int a, int b) {
	a = get_father(a);
	b = get_father(b);
	if (a == b)
		return false;
	father[b] = a;
	return true;
}

void make_apm() {
	for (int i = 1; i <= n; ++i)
		father[i] = i;
	
	A = B = C = 0;

	for (int i = 1; i <= m; ++i) {
		bool ok = unite(edge[i].x, edge[i].y);
		if (ok) {
			A += edge[i].a;
			B += edge[i].b;
			C += edge[i].c;
		}
	}
}

double rez = 1.0 * 100000000;
double poz = 0.0;

double comp(double t) {
	return A * t * t + B * t + C;
}

void get_min(double &a, double b) {
	if (a > b)
		a = b;
}

void check(double t) {
	double _rez = comp(t);
	if (rez > _rez) {
		rez = _rez;
		poz = t;
	}
}

int main() {
	in >> n >> m;
    for (int i = 1; i <= m; ++i) {
		in >> edge[i].x >> edge[i].y >> edge[i].a >> edge[i].b >> edge[i].c;
		edge[i].x++;
		edge[i].y++;
	}
	for (int i = 1; i <= m; ++i)
		for (int j = i + 1; j <= m; ++j) {
			pair<double, double> points = edge[i].cross(edge[j]);
			events.push_back(points.first);
			events.push_back(points.second);
		}
	events.push_back(-10000000.0);
	events.push_back(+10000000.0);
	sort(events.begin(), events.end());
	
	events.resize(unique(events.begin(), events.end()) - events.begin()); // pe double dar traiesc periculos
	for (int i = 0; i + 1 < events.size(); ++i) {
		double st = events[i];
		double dr = events[i + 1];
		t = (st + dr) / 2;

		sort(edge + 1, edge + m + 1);
		make_apm();

		double mid = -B / 2.0 / A;

//		cerr << st << '\t' << dr << '\n';
//		cerr << A << '\t' << B << '\t' << C << '\n';
//		cerr << "\n";

		if (st <= mid and mid <= dr) {
 			check(mid);
		} else {
			check(st);
			check(dr);
		}
	}
//	out << poz << ' ' << rez << '\n';
	freopen("mst.out", "w", stdout);
	printf("%.9lf %.9lf\n", poz, rez);
	return 0;
}
