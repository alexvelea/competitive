#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int kMaxN = 2005;

pair<int, int> bfs[kMaxN * kMaxN], best[kMaxN][kMaxN];
vector<pair<int, int> > vertex[kMaxN][kMaxN];
bool viz[kMaxN][kMaxN];
int n, m, dr;
string T[kMaxN];

void MakeBfs() {
	int st = 1;
	while (st <= dr) {
		int x = bfs[st].first;
		int y = bfs[st].second;
		for (int i = 0; i < int(vertex[x][y].size()); ++i) {
			int nx = vertex[x][y][i].first;
			int ny = vertex[x][y][i].second;
			if (viz[nx][ny] == false) {
				bfs[++dr] = make_pair(nx, ny);
				viz[nx][ny] = true;
			} else {
				// impossilble
				// better make an assert?
			}
		}
		++st;
	}
}

int a, b;

void get_best(int x, int y) {
	if (a < x) {
		b = max(a, y);
		a = x;
		return ;
	}
	if (b < x)
		b = x;
}

int dx[4] = {0, -1, 0, +1};
int dy[4] = {-1, 0, +1, 0};

int main() {
	cin >> n >> m;
 	for (int i = 0; i < n; ++i)
		cin >> T[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			int d;
			if (T[i][j] == '#')
				d = -1;
			if (T[i][j] == '<')
				d = 0;
			if (T[i][j] == '^')
				d = 1;
			if (T[i][j] == '>')
				d = 2;
			if (T[i][j] == 'v')
				d = 3;

			if (d == -1)
				continue;
			int nx, ny;
 			nx = i + dx[d];
			ny = j + dy[d];
			vertex[nx][ny].push_back(make_pair(i, j));
		}
 	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (T[i][j] == '#') {
				bfs[++dr] = make_pair(i, j);
				viz[i][j] = true;
			}
	MakeBfs();
	if (dr != n * m) {
		cout << "-1\n";
		return 0;
	}
	for (int i = dr; i; --i) {
		vector<int> mx;
		int x = bfs[i].first;
		int y = bfs[i].second;
		for (int i = 0; i < int(vertex[x][y].size()); ++i) {
	    	int nx = vertex[x][y][i].first;
			int ny = vertex[x][y][i].second;
			mx.push_back(1 + best[nx][ny].first);
			mx.push_back(1 + best[nx][ny].second);
		}
		sort(mx.begin(), mx.end());
		if (T[x][y] != '#')
			mx.resize(unique(mx.begin(), mx.end()) - mx.begin());
		reverse(mx.begin(), mx.end());
        mx.push_back(0);
		mx.push_back(0);
 		get_best(mx[0], mx[1]);
		best[x][y] = make_pair(mx[0], mx[1]);
	}
	cout << a + b;
	return 0;
}
