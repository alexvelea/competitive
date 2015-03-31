//Problem d from codeforcesRound297
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 2005;

void getMax(int &a, int b) {
	if (a < b)
		a = b;
}

void getMin(int &a, int b) {
	if (a > b)
		a = b;
}

queue<pair<int, int> > bf;

bool inside[kMaxN][kMaxN];

void insert(int x, int y) {
	if (not inside[x][y]) {
		inside[x][y] = true;
		bf.push(make_pair(x, y));
	}
}

struct Coord {
	int maxX, minX, maxY, minY;
	void join(Coord &rhs) {
		insert(maxX, minY);
		insert(maxX, maxY);
		insert(minX, minY);
		insert(minX, maxY);
 		insert(rhs.maxX, rhs.minY);
		insert(rhs.maxX, rhs.maxY);
		insert(rhs.minX, rhs.minY);
		insert(rhs.minX, rhs.maxY);   	
		getMax(maxY, rhs.maxY);
		getMax(maxX, rhs.maxX);
		getMin(minX, rhs.minX);
		getMin(minY, rhs.minY);
	}
	Coord() {}
	Coord(int x, int y) {
		maxX = minX = x;
		maxY = minY = y;
	}
} C[kMaxN * kMaxN];

int getC(int x, int y) {
	return (x - 1) * kMaxN + y;
}

int father[kMaxN * kMaxN];
int deep[kMaxN * kMaxN];

int getFather(int x) {
	if (father[x] != x)
		father[x] = getFather(father[x]);
	return father[x];
}

void uni(int x, int y) {
	x = getFather(x);
	y = getFather(y);

    if (x == y)
		return ;

	if (deep[x] > deep[y]) 
		;
	else
		swap(x, y);
	father[y] = x;
	C[x].join(C[y])
	;
	if (deep[x] == deep[y])
		++deep[x];
}

string el[kMaxN];
bool viz[kMaxN][kMaxN];

int main() {
	ios::sync_with_stdio(false);
 	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		string txt; cin >> txt;
		el[i] = "#";
		el[i] += txt;
		el[i] += '#';
	}
	for (int j = 0; j <= m; ++j) {
		el[0] += '#';
		el[n + 1] += '#';
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
 			C[getC(i, j)] = Coord(i, j); 			 
			father[getC(i, j)] = getC(i, j);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
 			if (not viz[i][j] and el[i][j] == '.') {
				// bfs
                bf.push(make_pair(i, j));
				viz[i][j] = true;
				while (bf.size()) {
					pair<int, int> c = bf.front();
					bf.pop();
					int x = c.first, y = c.second;
					inside[x][y] = false;
 					int dx[4] = {1, -1, 0, 0};
					int dy[4] = {0, 0, -1, 1};

					for (int d = 0; d < 4; ++d) {
						int xn = x + dx[d], yn = y + dy[d];
						if (viz[xn][yn] == false and el[xn][yn] == '.') {
							viz[xn][yn] = true;
							insert(xn, yn);
							uni(getC(xn, yn), getC(x, y));
						}
						if (el[xn][yn] == '.') {
							uni(getC(xn, yn), getC(x, y));
						}
					}
					int f = getFather(getC(x, y));
					for (int d = 0; d < 4; ++d) {
						int xn = x + dx[d];
						int yn = y + dy[d];
						if (el[xn][yn] == '*' and C[f].minX <= xn and xn <= C[f].maxX and C[f].minY <= yn and yn <= C[f].maxY) {
							el[xn][yn] = '.';
							viz[xn][yn] = true;
							insert(xn, yn);
							uni(getC(xn, yn), f);
						}
					}
				}
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout << el[i].substr(1, m) << '\n';
	}
	return 0;
}
