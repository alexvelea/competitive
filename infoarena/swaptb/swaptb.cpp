//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("swaptb.in");
ofstream out("swaptb.out");

const int inf = 0x3f3f3f3f;

int dx[] = {0, +1};
int dy[] = {+1, 0};

struct State {
	int el[10][10];
	State() {
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
				el[i][j] = 0;
	}

	bool empty() {
		bool ok = true;
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
				ok = ok & (el[i][j] == 0);
		return ok;
	}

	bool make_move() {
		bool ok = false;
		for (int j = 0; j < 10; ++j) {
			int down = 9;
			for (int up = 9; up >= 0; --up) {
				if (el[up][j] != 0) {
					el[down][j] = el[up][j];
					if (down != up) {
						el[up][j] = 0;
						ok = true;
					}
					--down;
				}
			}
		}
		int last[10][10];
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
				last[i][j] = el[i][j];

		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j) {
				if (last[i][j] == 0)
					continue;
				if (i + 2 < 10 and last[i][j] == last[i + 1][j] and last[i + 1][j] == last[i + 2][j])
					el[i][j] = el[i + 1][j] = el[i + 2][j] = 0, ok = true;
				if (j + 2 < 10 and last[i][j] == last[i][j + 1] and last[i][j + 1] == last[i][j + 2])
					el[i][j] = el[i][j + 1] = el[i][j + 2] = 0, ok = true;
			}
		return ok;
	}

	void make_move(int x, int y, int d) {
		int xp = dx[d] + x;
		int yp = dy[d] + y;
 		if (xp == -1 or yp == -1 or xp == 10 or yp == 10) 
			return ;
 		swap(el[x][y], el[xp][yp]);
		while (make_move()) {
/*			debug();
			int a;
			cin >> a;*/
		}
	}

	void debug() {
		for (int i = 0; i < 10; ++i, cerr << '\n')
			for (int j = 0; j < 10; ++j)
				cerr << el[i][j];
		cerr << "\n\n";
	}
} init;

void read() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			in >> init.el[i][j];
}

struct st_move {
	int x, y, d;
	st_move() {
		x = y = d = 0;
	}
	st_move(int _x, int _y, int _d) {
		x = _x;
		y = _y;
		d = _d;
	}
} ;

int nr_p = 0;

vector<st_move> bt(int remaining, State st) {
	vector<st_move> rez;
	if (st.empty()) { 
		nr_p++;
		rez.push_back(st_move());
		return rez;
	}

	if (remaining == 0)
		return rez;
	
	for (int i = 0; i < 10; ++i) 
		for (int j = 0; j < 10; ++j)
			if (st.el[i][j] != 0) {
				for (int d = 0; d < 2; ++d) {
					State st2 = st;
					st2.make_move(i, j, d);
					rez = bt(remaining - 1, st2);
					if (rez.size()) {
						rez.push_back(st_move(i, j, d));
						return rez;
					}
				}
			}
	return rez;
}

int main() {
	read();
 	init.make_move();
	init.debug();
	int x;
	cin >> x;
	vector<st_move> rez = bt(x, init);
	cerr << rez.size() << '\n';
	for (int i = int(rez.size()) - 1; i > 0; --i) {
		cerr << rez[i].x << '\t' << rez[i].y << '\t' << dx[rez[i].d] << '\t' << dy[rez[i].d] << '\n';
	}
	cerr << "!!!!\t" << nr_p << '\n';
    return 0;
}
