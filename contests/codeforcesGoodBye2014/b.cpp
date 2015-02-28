//Problem B from Codeforces Round good.bye.2014
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

const int inf = 0x3f3f3f3f, kMaxN = 305;

bool ok[kMaxN][kMaxN];
bool reacheable[kMaxN][kMaxN];
int el[kMaxN];

int bfs[kMaxN], dr;

int main() {
	int n;
    cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			char c;
			cin >> c;
			ok[i][j] = c - '0';
		}
	
    for (int i = 1; i <= n; ++i) {
		int nod = i;
		reacheable[nod][nod] = true;
		dr = 1;
		bfs[dr] = nod;
		while (dr) {
			nod = bfs[dr--];
			for (int j = 1; j <= n; ++j)
				if (ok[nod][j] and reacheable[i][j] == 0) {
					reacheable[i][j] = true;
					bfs[++dr] = j;
				}
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j)
			if (reacheable[i][j] and el[i] > el[j])
				swap(el[i], el[j]);
	}

	for (int i = 1; i <= n; ++i)
		cout << el[i] << ' ';
	return 0;
}
