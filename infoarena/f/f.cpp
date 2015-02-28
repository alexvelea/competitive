//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>
#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

#define int64 long long

ifstream in("f.in");
ofstream out("f.out");

struct Path {
	int x, y, c;
	string r;
	bool operator < (const Path &rhs) const{
		if (c == rhs.c)
			return x * 10000 + y < rhs.x * 10000 + rhs.y;
		return c < rhs.c;
	}
};

vector<Path> rez;


const int kMaxC = 5005, kMaxP = 1000005;

pair<int, int> coord[2][kMaxP], null_pair;
int r, c;

int other_start_point[kMaxP];
int start_point[kMaxC][kMaxC], end_point[kMaxC][kMaxC];

pair<int, int> father[kMaxC][kMaxC];
pair<int, int> child[kMaxC][kMaxC];
queue<pair<int, int> > dfs;

bool merge_point[kMaxC][kMaxC];

int viz[kMaxC][kMaxC];
bool dfs_viz[kMaxC][kMaxC];

int dx[4] = {-1, 0, +1, 0};
int dy[4] = {0, +1, 0, -1};

int get_d[26];
char dir_name[4] = {'N', 'E', 'S', 'W'};

int get_dir(pair<int, int> a, pair<int, int> b) {
	if (a.first - 1 == b.first)
		return 0;
	if (a.first + 1 == b.first)
		return 2;
	if (a.second + 1 == b.second)
		return 1;
	return 3;
}

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
 
bool inside(pair<int, int> C) {
	if (C.first == 0 or C.second == 0 or C.first == r + 1 or C.second == c + 1)
		return false;
	return true;
}                 

bool sure_path(int x, int y) {
	int rez = 0;
	for (int d = 0; d < 4; ++d) {
 		int nx = dx[d] + x;
		int ny = dy[d] + y;
 		if (inside(make_pair(nx, ny)) and viz[nx][ny] == 0)
			++rez;
		if (inside(make_pair(nx, ny)) and viz[nx][ny] == viz[x][y] and end_point[nx][ny] == true)
			++rez;
	}
	if (rez == 1)
		return true;
	return false;
}

bool sure_path(pair<int, int> p) {
	return sure_path(p.first, p.second);
}

int distance(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void normal_path(int x, int y) {
	Path P;
	P.x = x;
	P.y = y;
	P.c = viz[x][y];
//	cerr << x << '\t' << y << "!@?\n";
//	cerr << child[x][y].first << '\t' << child[x][y].second << "!!\n";
	while (child[x][y] != null_pair and merge_point[x][y] == false) {
		P.r += dir_name[get_dir(make_pair(x, y), child[x][y])];
		int nx, ny;
		nx = child[x][y].first;
		ny = child[x][y].second;
		x = nx;
		y = ny;
//		cerr << x << '\t' << y << "!!!\n";
		dfs_viz[x][y] = true;
	}
	if (merge_point[x][y] == true) {
//		cerr << "PENIS!";
 		P.r += dir_name[get_dir(make_pair(x, y), child[x][y])];   	
		int nx, ny;
		nx = child[x][y].first;
		ny = child[x][y].second;

		x = nx;
		y = ny;
		dfs_viz[x][y] = true;

		while (father[x][y] != null_pair) {
			P.r += dir_name[get_dir(make_pair(x, y), father[x][y])];
			int nx, ny;
			nx = father[x][y].first;
			ny = father[x][y].second;
			x = nx;
			y = ny;
//			cerr << x << '\t' << y << "###!@!!\n";
			dfs_viz[x][y] = true;
		}
	}	
 	rez.push_back(P);
}


int main() {
int nr_tests;
in >> nr_tests;
out << nr_tests << ' ';
while (nr_tests--) {
	out << '\n';
	int nr_p;
	in >> r >> c;
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j) {
			viz[i][j] = false;
			start_point[i][j] = 0;
			end_point[i][j] = 0;

			merge_point[i][j] = 0;
            father[i][j] = child[i][j] = make_pair(0, 0);
			dfs_viz[i][j] = 0;
		}
	
	in >> nr_p;

    for (int i = 1; i <= nr_p; ++i) {
		coord[0][i] = coord[1][i] = null_pair;	
		other_start_point[i] = 0;
	}
	rez.clear();

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
		end_point[get_coord(x).first][get_coord(x).second] = true;
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
		bool ok = true;

		for (int t = 1; t <= n and ok; ++t) {
			char c = C[t];
			int d = get_d[c - 'A'];
			coord_p.first += dx[d];
			coord_p.second += dy[d];
			viz[coord_p.first][coord_p.second] = color;
		}
	}
    for (int i = 1; i <= nr_p; ++i)
		for (int p = 0; p < 2; ++p) {
//			cerr << coord[p][i].first << ' ' << coord[p][i].second << '\n';
            if (sure_path(coord[p][i].first, coord[p][i].second)) {
				dfs.push(make_pair(coord[p][i].first, coord[p][i].second));
				dfs_viz[coord[p][i].first][coord[p][i].second] = true;
			}
		}

	while (dfs.size()) {
		pair<int, int> pi = dfs.front();
		dfs.pop();
		int x = pi.first;
		int y = pi.second;
		for (int d = 0; d < 4; ++d) {
			int nx = dx[d] + x;
			int ny = dy[d] + y;
 			if (viz[nx][ny] == 0 and inside(make_pair(nx, ny))) {
				// am gasit
//				cerr << nx << '\t' << ny << "!!!!!!!\n";
				viz[nx][ny] = viz[x][y];
				end_point[nx][ny] = true;
				end_point[x][y] = false;
				father[nx][ny] = make_pair(x, y);
				child[x][y] = make_pair(nx, ny);
				break;
			}
			if (viz[nx][ny] == viz[x][y] and end_point[nx][ny] == true and inside(make_pair(nx, ny))) {
				// merge
				end_point[nx][ny] = false;
				end_point[x][y] = false;
				child[nx][ny] = make_pair(x, y);
				child[x][y] = make_pair(nx, ny);
				merge_point[x][y] = merge_point[nx][ny] = true;
			}
		}
		
		for (int d = 0; d < 4; ++d) {
			int nx = dx[d] + x;
			int ny = dy[d] + y;
//			cerr << x << '\t' << y << '\t' << nx << '\t' << ny << '\t' << sure_path(nx, ny) << '\t' << dfs_viz[nx][ny] << '\t' << end_point[nx][ny] << '\n';
			if (inside(make_pair(nx, ny)) and sure_path(nx, ny) and dfs_viz[nx][ny] == false and end_point[nx][ny]) {
	        	dfs_viz[nx][ny] = true;
				dfs.push(make_pair(nx, ny));
			}
		}
	}

	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			dfs_viz[i][j] = 0;

	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (child[i][j] != null_pair and start_point[i][j] and dfs_viz[i][j] == 0) {
				normal_path(i, j);
			}
		}
	}
	sort(rez.begin(), rez.end());
 	out << rez.size() << ' ';
	for (int i = 0; i < int(rez.size()); ++i) {
		out << rez[i].c << ' ' << (rez[i].x - 1) * c + rez[i].y << ' ' << rez[i].r.size() << ' ';
		for (int j = 0; j < int(rez[i].r.size()); ++j)
			out << rez[i].r[j] << ' ';
	}

} 
return 0;
}
