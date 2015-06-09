//Problem verlab from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 105;

ifstream fin("verlab.in");
ofstream fout("verlab.out");

int dx[4] = {0, +1, 0, -1};
int dy[4] = {-1, 0, +1, 0};

pair<int, int> father[kMaxN][kMaxN];    
bool viz[kMaxN][kMaxN], ok = true;

int el[kMaxN][kMaxN];

int n, m;

void df(int x, int y) {
	viz[x][y] = true;
	for (int d = 0; d < 4; ++d) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (not ((el[x][y] & (1 << d)) or (el[nx][ny] & (1 << (d ^ 2) )))) {
//			cerr << x << '\t' << y << '\t' << nx << '\t' << ny << '\n';
			// gol
			if (not viz[nx][ny]) {
				if (nx == 0 or nx == n + 1 or ny == 0 or ny == m + 1) {
					ok = false;
				} else {
					father[nx][ny] = make_pair(x, y);
					df(nx, ny);
				}
			} else {
				if (father[x][y] != make_pair(nx, ny)) {
					ok = false;
				}
			}
		} else {
			if ((el[x][y] & (1 << d)) and (el[nx][ny] & (1 << (d ^ 2)))) {
				ok = false;
			}
		}
	}
}

int main() {
	int t; fin >> t;
	while (t--) {
		fin >> n >> m;
		memset(el, 0, sizeof(el));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				fin >> el[i][j];
				viz[i][j] = false;
				father[i][j] = {0, 0};
			}
		}
		ok = true;
		df(1, 1);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (viz[i][j] == false) {
					ok = false;
				}
			}
		}
		fout << ok << '\n';
	}
	return 0;
}
