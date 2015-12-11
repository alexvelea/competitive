#include <cassert>
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

#define int64 long long

ifstream in("laser.in");
//ofstream out("laser.out");

const int kMaxN = 520;
const double pi = 3.1415926535, eps = 0.000000001;

struct Segm {
	double x, y;
	
	Segm() {
		x = y = 0.0;
	}

	Segm(double x1, double y1, double x2, double y2) {
		x = atan2(y1, x1);
		y = atan2(y2, x2);
 		if (x < 0.0)
			x += 2.0 * pi;
		if (y < 0.0)
			y += 2.0 * pi;
		if (x > y)
			swap(x, y);
	}
	
	bool inside(double c) {
		if (x + pi >= y) {
			if (x <= c + eps and c <= y + eps)
				return true;
			return false;
		} else {
			if (y <= c + eps and c <= x + 2.0 * pi + eps)
				return true;
			if (y <= c + 2.0 * pi + eps and c + 2.0 * pi <= x + 2.0 * pi + eps)
				return true;
 			return false;
		}
	}
} S[kMaxN];

vector<double> Event, Query;
bitset<kMaxN> Ecu[kMaxN];

bool viz[kMaxN];
int sol[kMaxN];

int main() {
	int n;
 	in >> n;
	for (int i = 1; i <= n; ++i) {
		double x1, y1, x2, y2;
		in >> x1 >> y1 >> x2 >> y2;
		S[i] = Segm(x1, y1, x2, y2);
//		cerr << S[i].x * 180.0 / pi << '\t' << S[i].y * 180.0 / pi << '\n';
		Event.push_back(S[i].x);
		Event.push_back(S[i].y);
	}
	sort(Event.begin(), Event.end());
	Event.push_back(Event[0] + 2.0 * pi);
	for (int st = 0; st < int(Event.size()); ) {
		int dr = st;
		while (dr < int(Event.size()) and fabs(Event[dr] - Event[st]) < eps)
			++dr;
		if (dr == int(Event.size()))
 			break;
		double x = (Event[st] + Event[dr]) / 2.0;
		if (x >= 2.0 * pi)
			x -= 2.0 * pi;
		Query.push_back(x);
		st = dr;
	}
	int q = Query.size();
	for (int i = 1; i <= n; ++i) {
		bool st;
		in >> st;
		Ecu[i][q] = st;
	}
//	for (int i = 0; i < q; ++i)
//		cerr << i << '\t' << Query[i] * 180.0 / pi << '\n';
	for (int i = 1; i <= n; ++i) {
//		cerr << i << ":\t";
		for (int j = 0; j < q; ++j)
			if (S[i].inside(Query[j])) {
				Ecu[i][j] = true;
//				cerr << j << "#\t";
			}
//		cerr << '\n';
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < q; ++j)
			if (not viz[j] and Ecu[i][j] == true) {
				sol[i] = j;
				viz[j] = true;
				break;
			}
		for (int j = 1; j <= n; ++j)
			if (Ecu[j][sol[i]] == true and i != j)
 				Ecu[j] ^= Ecu[i];
	}

	vector<double> rez;

	for (int i = 1; i <= n; ++i) {
		if (Ecu[i][q] == true)
			rez.push_back(Query[sol[i]] * 180.0 / pi);
	}
                
	freopen("laser.out", "w", stdout);

	printf("%d\n", int(rez.size()));
	for (int i = 0; i < int(rez.size()); ++i) {
		printf("%.7lf\n", rez[i]);
		assert(rez[i] >= 0.0);
 		assert(rez[i] <= 360.0);
	}
	
	return 0;
}
