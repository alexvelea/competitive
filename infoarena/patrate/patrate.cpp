#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int max_n = 500005, INF = 0x3f3f3f3f;

ifstream in("patrate.in");
ofstream out("patrate.out");

int n;

void get_min (int &a, int b) {
	if (a > b)
		a = b;
}
void get_max (int &a, int b) {
	if (a < b)
		a = b;
}

struct stare {
	int min_x, min_y, max_x, max_y;
	vector < pair<int,int> > coord;
	stare() {
		min_x = INF;
		min_y = INF;
		max_x = -INF;
		max_y = -INF;
	}
	void push (int x, int y) {
		get_min (min_x, x);
		get_min (min_y, y);
		get_max (max_x, x);
		get_max (max_y, y);
		coord.push_back (make_pair(x, y));
	}
	void push (pair<int,int> xy) {
		get_min (min_x, xy.first);
		get_min (min_y, xy.second);
		get_max (max_x, xy.first);
		get_max (max_y, xy.second);
		coord.push_back(xy);
	}
	bool empty(int h) {
		if (coord.size() == 0)
			return true;
		if (max_x - min_x <= h && max_y - min_y <= h)
			return true;
		return false;
	}
	stare put_square (int h) {
		stare rez;
		int max_x = min_x + h;
		int max_y = min_y + h;
		for (int i = 0; i < int(coord.size()); ++i) {
			if (min_x <= coord[i].first && coord[i].first <= max_x && 
				min_y <= coord[i].second && coord[i].second <= max_y)
				;
			else
				rez.push(coord[i]);
		}
		return rez;
	}
	void rotate() {
		min_x = INF;
		min_y = INF;
		max_x = -INF;
		max_y = -INF;
		for (int i = 0; i < int(coord.size()); ++i) {
			swap (coord[i].first, coord[i].second);
			coord[i].second *= -1;
			get_min (min_x, coord[i].first);
			get_min (min_y, coord[i].second);
			get_max (max_x, coord[i].first);
			get_max (max_y, coord[i].second);
		}
	}
} initial;

bool square2 (int h, stare st) {
	for (int i = 1; i <= 4; ++i) {
		int min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
		for (int i = 0; i < int(st.coord.size()); ++i)
			if (st.min_x <= st.coord[i].first && st.coord[i].first <= st.min_x + h &&
				st.min_y <= st.coord[i].second && st.coord[i].second <= st.min_y + h)
				;
			else {
				get_min (min_x, st.coord[i].first);
				get_min (min_y, st.coord[i].second);
				get_max (max_x, st.coord[i].first);
				get_max (max_y, st.coord[i].second);
			}
		if (min_x == INF || (max_x - min_x <= h && max_y - min_y <= h))
			return true;
		st.rotate();
    }
	return false;
}

bool square3 (int h, stare st) {
	bool ok = false;
	for (int i = 1; i <= 4 && !ok; ++i) {
		ok = max (ok, square2(h, st.put_square(h)));
		st.rotate();
	}
	return ok;
}

int main() {
	in >> n;
	if (n <= 3) {
		out << "0\n";
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		int x, y;
		in >> x >> y;
		initial.push(x,y);
	}
	int rez = 0;
	for (int p = 15; p >= 0; --p) {
		if (square3(rez + (1<<p), initial))
			;
		else
  		rez += (1<<p);
	}
	++rez;
	out << rez << "\n";
	return 0;
}
