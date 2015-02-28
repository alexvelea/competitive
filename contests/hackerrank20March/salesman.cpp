#include <iostream>
using namespace std;

#define DEBUG 1

const int kMaxN = 10, inf = 0x3f3f3f3f;

const int dx[] = {0, +1, 0, -1};
const int dy[] = {-1, 0, +1, 0};
int cost[kMaxN][kMaxN][4];

int n, m;

void generate_line(int l, int c, int state, int _cost) {
	if (c == m) {
		get_min(best[l][state], _cost);
		return ;
	}
	if (viz[c] == true)
		return ;
	_cost += cost[l][c][2];
	for (int C = c + 1; c < m and viz[C] == false; ++c) {
		_cost += cost[l][C][3];
		generate_line(l, C + 1, state | (1 << c) | (1 << C), _cost + cost[l][C][2]);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < m; ++j) {
			int el;
			cin >> el;
			cost[i][j][1] = cost[i][j + 1][3] = el;
		}
	for (int i = 1; i < n; ++i)
		for (int j = 1; j <= m; ++j) {
			int el;
			cin >> el;
			cost[i][j][2] = el;
		}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < (1 << m); ++j)
			best[i][j] = inf;
	}

    generate_line(0, 0, 0, 0);
 	for (int i = 0; i + 1 < n; ++i) {
		for (int j = 0; j < (1 << m); ++j)
			if (best[i][j] != inf) {
				expand(i, j, best[i][j]);
			}
	}
	for (int j = 0; j < (1 << m); ++j)
		if (best[n - 2][j] != inf) {
			finish(n - 1, j, best[n - 2][j]);
		}
  	 cout << rez << '\n';
}
