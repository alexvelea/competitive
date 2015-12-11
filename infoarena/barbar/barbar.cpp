#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

ifstream in("barbar.in");
ofstream out("barbar.out");

const int kMaxN = 1005;

queue<pair<int, int> > bfs;
int father[kMaxN][kMaxN], fth[kMaxN * kMaxN], nr_f;
int best[kMaxN][kMaxN];
bool ok[kMaxN][kMaxN], viz[kMaxN][kMaxN];
vector<pair<int, int> > el[kMaxN * 2];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int get_father(int f) {
	if (fth[f] != f)
		fth[f] = get_father(fth[f]);
	return fth[f];
}

void join(int a, int b) {
	a = get_father(a);
	b = get_father(b);
	if (a == 0 or b == 0)
		return ;
	fth[a] = b;
	return ;
}

int get_father(int x, int y) {
	int f = get_father(father[x][y]);
	father[x][y] = f;
	return f;
}

int main() {
	int n, m;
	int x_st, y_st, x_fi, y_fi;
	in >> n >> m;
 	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			ok[i][j] = true;
			char c;
			in >> c;
			if (c == '.')
				continue;
			if (c == '*') {
				ok[i][j] = false;
				continue;
			}
			if (c == 'D') {
				viz[i][j] = true;
				bfs.push(make_pair(i, j));
				continue;
			}
			if (c == 'I') {
				// irod barmanul
				x_st = i;
				y_st = j;
				continue;
			}
			if (c == 'O') {
				// iubita lui irod
				x_fi = i;
				y_fi = j;
				continue;
			}
		}
	while (bfs.size()) {
		int x = bfs.front().first;
		int y = bfs.front().second;
		bfs.pop();

		for (int d = 0; d < 4; ++d) {
			int nx = dx[d] + x;
			int ny = dy[d] + y;
			if (viz[nx][ny] == false and ok[nx][ny]) {
				viz[nx][ny] = true;
				best[nx][ny] = best[x][y] + 1;
				bfs.push(make_pair(nx, ny));
			}
		}
	}
//	for (int i = 1; i <= n; ++i, cerr << '\n')
//		for (int j = 1; j <= m; ++j)
//			cerr << best[i][j];

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			el[best[i][j]].push_back(make_pair(i, j));
	for (int i = n + m; i > 0; --i) {
		for (pair<int, int> itr : el[i]) {
			int c = 0;
			int x = itr.first;
			int y = itr.second;
			for (int d = 0; d < 4; ++d) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (c == 0)
					c = get_father(nx, ny);
				else
					join(c, get_father(nx, ny));
			}
			if (c == 0) {
				++nr_f;
				fth[nr_f] = nr_f;
				c = nr_f;
			}
			father[x][y] = c;
		}

/* 		for (int i = 1; i <= n; ++i, cerr << '\n')
			for (int j = 1; j <= m; ++j)   	
				if (father[i][j])
					cerr << '1';
				else
					cerr << '0';
		cerr << '\n';*/

 		if (get_father(x_st, y_st) == get_father(x_fi, y_fi) and get_father(x_st, y_st) != 0) {
			out << i << '\n';
			return 0;
		}          	
	}
	out << "-1";
	return 0;
}
