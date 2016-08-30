#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

ifstream fin("tsunami.in");
ofstream fout("tsunami.out");

const int kMaxN = 1e3 + 5;
int el[kMaxN][kMaxN];
bool viz[kMaxN][kMaxN];

int dx[4] = {+1, -1, +0, +0};
int dy[4] = {+0, +0, -1, +1};

queue<pair<int, int> > bfs;

int main() {
	int n, m, k; fin >> n >> m >> k;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			fin >> el[i][j];
		}
	}

	for (int i = 1; i <= n; i += 1) {
		viz[i][0] = viz[i][m + 1] = true;
	}
	for (int i = 1; i <= m; i += 1) {
		viz[0][i] = viz[n + 1][i] = true;
	}

	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			if (el[i][j] == 0) {
				viz[i][j] = true;
				bfs.push({i, j});
			}
		}
	}

	while (bfs.size()) {
		int x = bfs.front().first, y = bfs.front().second;
		bfs.pop();
		for (int d = 0; d < 4; d += 1) {
			if (not viz[x + dx[d]][y + dy[d]] and el[x + dx[d]][y + dy[d]] < k) {
				viz[x + dx[d]][y + dy[d]] = true;
				bfs.push({x + dx[d], y + dy[d]});
			}
		}
	}

	int rez = 0;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			if (viz[i][j] and el[i][j] != 0) {
				rez += 1;
			}
		}
	}

	fout << rez << '\n';
	return 0;
}