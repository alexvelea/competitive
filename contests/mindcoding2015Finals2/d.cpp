//Problem d from mindcodingFinalRound2
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1200;

int dirX[5] = {-1, +1, +0, +0, +0};
int dirY[5] = {+0, +0, -1, +1, +0};

char el[kMaxN][kMaxN];
bool viz[kMaxN][kMaxN];

void getMin(int &a, int b) {
	if (a > b) {
		a = b;
	}
}

void getMax(int &a, int b) {
	if (a < b) {
		a = b;
	}
}

int maxX, maxY;
int minX, minY;
int arie;

void df(int x, int y) {
	arie++;
	getMax(maxX, x);
	getMin(minX, x);
	getMax(maxY, y);
	getMin(minY, y);

	viz[x][y] = true;
	for (int j = 0; j < 5; ++j) {
	for (int i = 0; i < 5; ++i) {
		int nx = x + dirX[i] + dirX[j];
		int ny = y + dirY[i] + dirY[j];
 		if (viz[nx][ny] == false and el[nx][ny] == '1') {
			df(nx, ny);
		}
	} } 
}


bool count(int x, int y, int EPS) {
	for (int i = -EPS; i <= EPS; ++i) {
		for (int j = -EPS; j <= EPS; ++j) {
			if (x + i > 0 and y + j > 0 and x + i < kMaxN and y + j < kMaxN)
				if (el[x + i][y + j] == '1') {
					return true;
				}
		}
	}
	return false;
}

bool count(int x, int y) {
	return count(x, y, 3);
}

int rez[6];

int main() {
//	freopen("test.in", "r", stdin);
//	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) {
			cin >> el[i][j];
		}
/* 	for (int i = 1; i <= n; ++i, cout << '\n') 
		for (int j = 1; j <= m; ++j) {   	
			if (el[i][j] == '1') {
				cout << "*";
			} else {
				cout << ' ';
			}
		}*/
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (viz[i][j] == false and el[i][j] == '1') {
				minX = inf;
				maxX = 0;
				minY = inf;
				maxY = 0;
				arie = 0;
				df(i, j);
				int l = maxX - minX;
				int L = maxY - minY;

                // linie
				if (1.0 * l * L / arie <= 0.2 or (1.0 * max(l, L) / min(l, L) >= 3.0)) {
					rez[2]++;
					continue;
				}
				int c = count(minX, minY) + count(minX, maxY) + count(maxX, minY) + count(maxX, maxY);

				if (c == 1 or c == 2) {
					rez[3]++;
					continue;
				}

				bool ok = false;
				for (int p = 0; ; ++p) {
					if (count(minX, minY + p, 3) == 1) {
						if (count(maxX, maxY - p, 15) and abs(l - L) <= 20) {
							ok = true;
						}
						break;
					}
				}

				if (ok) {
					rez[4]++;
				} else {
					rez[5]++;
				}
			}
		}
	}
	for (int i = 2; i <= 5; ++i) {
		cout << i << ' ' << rez[i] << '\n';
	}
	return 0;
}
