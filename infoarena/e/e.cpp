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

ifstream in("e.in");
ofstream out("e.out");

const int kMaxC = 5005, kMaxP = 1000005;

int rez[kMaxP];

pair<int, int> coord[2][kMaxP], null_pair;
pair<int, int> bfs[kMaxC * kMaxC];

int r, c;

int other_start_point[kMaxP];
int start_point[kMaxC][kMaxC];
int Step[kMaxP];

int viz[kMaxC][kMaxC];
bool bf_viz[kMaxC][kMaxC];

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
int nr_tests;
in >> nr_tests;
while (nr_tests--) {
	int nr_p;
	in >> r >> c;
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j) {
			viz[i][j] = false;
			start_point[i][j] = 0;
		}
	
	in >> nr_p;

    for (int i = 1; i <= nr_p; ++i) {
		coord[0][i] = coord[1][i] = null_pair;	
		other_start_point[i] = 0;
		rez[i] = 0;
		Step[i] = 0;
	}

	nr_p /= 2;
	
	get_d['N' - 'A'] = 0;
    get_d['E' - 'A'] = 1;
	get_d['S' - 'A'] = 2;
	get_d['W' - 'A'] = 3;

	for (int i = 1; i <= 2 * nr_p; ++i) {
		int x, color;
		in >> x >> color;
	   	if (coord[0][color] == null_pair)
			coord[0][color] = get_coord(x);
		else {
			other_start_point[i] = start_point[coord[0][color].first][coord[0][color].second];
			other_start_point[other_start_point[i]] = i;
			coord[1][color] = get_coord(x);
		}
		start_point[get_coord(x).first][get_coord(x).second] = i;
		viz[get_coord(x).first][get_coord(x).second] = color;
	}

	int nr_paths;
	in >> nr_paths;
	for (int T = 1; T <= nr_paths; ++T) {
		int color, x, n;
		char C[kMaxP];
		in >> color >> x >> n;
		for (int i = 1; i <= n; ++i)
			in >> C[i];

		pair<int, int> coord_p = get_coord(x);
		rez[color] = 1;
		bool ok = true;

		for (int t = 1; t <= n and ok; ++t) {
			char c = C[t];
			int d = get_d[c - 'A'];
			coord_p.first += dx[d];
			coord_p.second += dy[d];
			viz[coord_p.first][coord_p.second] = color;
		}
	}
 	
	// verificam daca sunt unite
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			bf_viz[i][j] = 0;
	
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j) 
			bf_viz[i][j] = false;

	
	for (int step = 0, i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j) {
			if (viz[i][j] == 0 and bf_viz[i][j] == false) {
				++step;
				int st = 1;
				bfs[1] = make_pair(i, j);
				bf_viz[i][j] = true;
				while (st) {
					int x = bfs[st].first;
					int y = bfs[st].second;
					st--;
 					for (int d = 0; d < 4; ++d) {
						int nx = x + dx[d];
						int ny = y + dy[d];
						if (viz[nx][ny] == 0 and bf_viz[nx][ny] == 0 and inside(make_pair(nx, ny))) {
							st++;
							bfs[st] = make_pair(nx, ny);
							bf_viz[nx][ny] = true;
						}
						if (inside(make_pair(nx, ny)) and viz[nx][ny] and start_point[nx][ny]) {
							Step[start_point[nx][ny]] = step;
							if (Step[other_start_point[start_point[nx][ny]]] == step) {
								int color = viz[nx][ny];
								if (rez[color] == 0)
									rez[color] = 2;
							}
						}
					}
				}
			}
		}
/*	for (int t = 1; t <= nr_p; ++t) {
		if (rez[t] == 1)
			continue;
		int st = 1;
		for (int i = 1; i <= r; ++i)
			for (int j = 1; j <= c; ++j)
				bf_viz[i][j] = false;
		bfs[1] = coord[0][t];
		while (st > 0) {
			int x = bfs[st].first;
			int y = bfs[st].second;
			--st;
			for (int d = 0; d < 4; ++d) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (bf_viz[nx][ny] == 0) {
					bf_viz[nx][ny] = true;
                    if (make_pair(nx, ny) == coord[1][t]) {
						rez[t] = 2;
						st = -1000;
						break;
					}
					if (viz[nx][ny] == 0) {
						st++;
						bfs[st] = make_pair(nx, ny);
					}
				}
			}
		}
	}   */
	for (int i = 1; i <= nr_p; ++i) {
		if (rez[i] == 0 and distance(coord[0][i], coord[1][i]) == 1)
			rez[i] = 2;
		if (rez[i] == 0)
			rez[i] = 3;
		out << rez[i] << ' ';
	}
} 
return 0;
}
//Problem e from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("e.in");
ofstream out("e.out");

int main() {

	return 0;
}
