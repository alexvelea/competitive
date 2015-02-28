#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("adapost2.in");
ofstream out("adapost2.out");
const int max_n = 50005;
const double eps = 0.0000001;

int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, 1, -1, 0, 0};

struct coord{
	double x, y;
	coord() {
		x = y = 0;
	}
	void read() {
		double _x, _y;
		in >> _x >> _y;
		x = _x;
		y = _y;
	}
	double dist(double _x, double _y) {
		return sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));	
	}
} c[max_n];

double x, y;
int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) 
		c[i].read();
	x = y = 0.0;
	double p = 1024.0;
	for (int t = 25; t; --t) {
		double cost[5];
		for (int i = 0; i < 5; ++i)
			cost[i] = 0;
		for (int i = 1; i <= n; ++i)
			for (int d = 0; d < 5; ++d) 
				cost[d] += c[i].dist(x + dx[d] * p, y + dy[d] * p);
		double mn = cost[0];
		int poz = 0;
		for (int d = 1; d < 5; ++d)
			if (cost[d] + eps < mn) {
				poz = d;
				mn = cost[d];
			}
		if (poz) {
			t++;
			x += dx[poz] * p;
			y += dy[poz] * p;
		} else 
			p /= 2.0;
	}
  	out << x << ' ' << y << '\n';	
	return 0;
}
