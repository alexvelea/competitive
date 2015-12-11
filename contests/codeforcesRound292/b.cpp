//Problem B from Codeforces Round 292
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

const int inf = 0x3f3f3f3f, kMaxV = 2005 * 2005, kMaxN = 2005;
int n, m;

vector<int> vertex[kMaxV];
int match[kMaxV], sz[kMaxV];
char el[kMaxN][kMaxN];

inline int codif(int a, int b) {
	return a * (m + 2) + b;	
}

void solve(int nod) {
	for (auto itr : vertex[nod]) {
		if (match[itr] == 0) {
			int oth = itr;
			match[oth] = nod;
			match[nod] = oth;
			sz[oth] = sz[nod] = 0;
			for (auto itr2 : vertex[oth]) {
				sz[itr2]--;
				if (sz[itr2] == 1) {
					solve(itr2);
				}
			}
			return ;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> (el[i] + 1);
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if ((i + j) % 2 == 0) {
				int dx[] = {+1, -1, 0, 0};
				int dy[] = {0, 0, +1, -1};
				for (int d = 0; d < 4; ++d) {
					int x = i + dx[d];
					int y = j + dy[d];
					if (el[x][y] == '.' and el[i][j] == '.') {
						vertex[codif(i, j)].push_back(codif(x, y));
						sz[codif(i, j)]++;
						vertex[codif(x, y)].push_back(codif(i, j));
						sz[codif(x, y)]++;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int v = codif(i, j);
			if (sz[v] == 1) {
//				cerr << "!!!!\t" << v << '\n';
				solve(v);
			}
		}
	}
	bool ok = true;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (match[codif(i, j)] == 0 and el[i][j] == '.') {
				ok = false;  
			}
		}
	}
	
	if (ok) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (match[codif(i, j)]) {
					int v = codif(i, j);
					if (match[v] == codif(i + 1, j)) {
						el[i][j] = '^';
					}
					if (match[v] == codif(i - 1, j)) {
						el[i][j] = 'v';
					}
					if (match[v] == codif(i, j - 1)) {
						el[i][j] = '>';
					}
					if (match[v] == codif(i, j + 1)) {
						el[i][j] = '<';
					}
				}
//				cout << match[codif(i, j)] << "|" << codif(i, j) << '\t';
			}
			cout << (el[i] + 1);
			cout << '\n';
		}

	} else {
		cout << "Not unique\n";
	}
	return 0;
}
