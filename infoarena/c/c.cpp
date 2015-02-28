//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>
#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define int64 long long

ifstream in("c.in");
ofstream out("c.out");

const int kMaxC = 5005, kMaxP = 1000005;

int rez[kMaxP];

pair<int, int> coord[2][kMaxP], null_pair;
int r, c;

int viz[kMaxC][kMaxC];
int dx[4] = {-1, 0, +1, 0};
int dy[4] = {0, +1, 0, -1};

int get_d[26];

int abs(int a) {
	if (a > 0)
		return a;
	return -a;
}

pair<int, int> get_coord(int x) {
	int R, C;
	C = x % c;
	if (C == 0)
		C = c;
	R = (x - 1) / c;
	R++;
 	return make_pair(R, C);
}

int distance(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

bool inside(pair<int, int> C) {
	if (C.first == 0 or C.second == 0 or C.first == r + 1 or C.second == c + 1)
		return false;
	return true;
}

int main() {
	int n;
	in >> r >> c;
	in >> n;
	
	get_d['N' - 'A'] = 0;
    get_d['E' - 'A'] = 1;
	get_d['S' - 'A'] = 2;
	get_d['W' - 'A'] = 3;

	while (n--) {
		int x, color;
		in >> x >> color;
			
	   	if (coord[0][color] == null_pair)
			coord[0][color] = get_coord(x);
		else
			coord[1][color] = get_coord(x);
		viz[get_coord(x).first][get_coord(x).second] = 1;
	}
	int nr_paths;
	in >> nr_paths;
	for (int T = 2; T <= nr_paths + 1; ++T) {
		int color, x, n;
		char C[kMaxP];
		in >> color >> x >> n;
		for (int i = 1; i <= n; ++i)
			in >> C[i];

		pair<int, int> coord_p = get_coord(x);

		if (coord_p != coord[0][color])
			swap(coord[0][color], coord[1][color]);
		if (coord_p != coord[0][color]) {
			cerr << "SOMETHING IS REALLY BAD\n";
			assert(0);
		}

		bool ok = true;
		int bad = 0;

		for (int t = 1; t <= n and ok; ++t) {
			char c = C[t];
			int d = get_d[c - 'A'];
			coord_p.first += dx[d];
			coord_p.second += dy[d];
			if (not inside(coord_p)) {
				ok = false;
				out << "-1 " << t << '\n';
				bad = t;
				break;
			}
			if (t != n and viz[coord_p.first][coord_p.second]) {
				ok = false;
				out << "-1 " << t << '\n';
				bad = t;
				break;
			}
			if (viz[coord_p.first][coord_p.second] == 0)
				viz[coord_p.first][coord_p.second] = T;
		}
		if (ok == true) {
			if (coord_p == coord[1][color])
				out << "1 " << n << '\n';
			else {
				out << "-1 " << n << '\n';
				bad = n;
				ok = false;
			}
		}
		if (ok == false) {
			ok = true;
			coord_p = get_coord(x);
	 		for (int t = 1; t < bad and ok; ++t) {
				char c = C[t];
				int d = get_d[c - 'A'];
				coord_p.first += dx[d];
				coord_p.second += dy[d];
				if (viz[coord_p.first][coord_p.second] == T)
					viz[coord_p.first][coord_p.second] = 0;
			}
		}
	}
 	for (int i = 1; i <= r; ++i, cout << '\n', out << '\n')
		for (int j = 1; j <= c; ++j)
			if (viz[i][j]) {
				cout << '#';
				out << '#';
			} else {
				cout << ' ';
				out << ' ';
			}
 
	return 0;
}
