//Problem hallway from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long
typedef pair<int,int> pii;

const int inf = 0x3f3f3f3f, kMaxN = 1005;

ifstream in("hallway.in");
ofstream out("hallway.out");

pii coord[kMaxN];

int dist(pii a, pii b) {
	return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

void get_min(int &a, int b) {
	if (a > b)
		a = b;
}

int best[kMaxN];
bool viz[kMaxN];



int main() {
	int x, y, n;
	in >> x >> y; 
 	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> coord[i].first >> coord[i].second;
	for (int i = 1; i <= n; ++i)
		best[i] = coord[i].first * coord[i].first;
	for (int t = 1; t <= n; ++t) {
		int mn = inf, poz = -1;
		for (int i = 1; i <= n; ++i)
			if (not viz[i] and mn > best[i]) {
				mn = best[i];
				poz = i;
			}
		viz[poz] = true;
		for (int i = 1; i <= n; ++i)
			if (not viz[i])
				get_min(best[i], max(dist(coord[i], coord[poz]), best[poz]));
	}

	for (int i = 1; i <= n; ++i)
		best[i] = max(best[i], (y - coord[i].first) * (y - coord[i].first));
	int mn = inf;
	for (int i = 1; i <= n; ++i)
		get_min(mn, best[i]);
	out << fixed << setprecision(9) << sqrt(mn) / 2.0 << '\n'; 

	return 0;
}
