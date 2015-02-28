// 9:35
//Problem acm_2014_e from Infoarena
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

const int inf = 0x3f3f3f3f;

ifstream in("acm_2014_e.in");
ofstream out("acm_2014_e.out");

vector<pair<int, int> > points;

void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

void get_min(int &a, int b) {
	if (a > b)
		a = b;
}

void rotate() {
	for (int i = 0; i < int(points.size()); ++i) {
		int x = points[i].first;
		int y = points[i].second;
 		points[i].second = x;
		points[i].first = -y;
	}
}

double solve() {
	sort(points.begin(), points.end());
    int x = points[0].first, y = -inf, my = -inf, cy = +inf;
	double sqr = sqrt(2), cost = 0.0;
	for (auto itr : points) {
		if (x == itr.first) {
			get_max(y, itr.second);
			get_min(cy, itr.second);
		}
		get_max(my, itr.second);
	}

	cost += y - cy;

	for (auto itr : points) {
		if (itr.second >= y) {
			int d = itr.first - x;
			if (d + y > my)
				d = my - y;
			x += d;
			y += d;
			cost += 1.0 * sqr * d;
			cost += itr.first - x;
			x = itr.first;
			if (y < itr.second) {
				cost += itr.second - y;
				y = itr.second;
			}
		}
		if (itr.second == my)
			break;
	}
	return cost;
}	

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y;
   		in >> x >> y;
		points.push_back(make_pair(x - 1, y));
 		points.push_back(make_pair(x, y + 1));   	
 		points.push_back(make_pair(x + 1, y));   	
 		points.push_back(make_pair(x, y - 1));   	
	} 
	
 	double rez = 0.0;
	for (int i = 0; i < 4; ++i) {
		rez += solve();
		rotate();
	}

	out << fixed << setprecision(10) << rez << '\n';
	return 0;
}
