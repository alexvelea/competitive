//Problem D from Codeforces Round usaco2015JanBronz
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("meeting.in");
ofstream out("meeting.out");

map<int, bool> pos[2];

int cost[2][20][20];

void bt(int ind, int a, int b, int _cost) {
	if (a == b) {
		pos[ind][_cost] = true;
	} else {
		for (int i = a + 1; i <= b; ++i) {
			if (cost[ind][a][i] != inf) {
				bt(ind, i, b, _cost + cost[ind][a][i]);
			}
		}
	}
}

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			cost[0][i][j] = inf;
			cost[1][i][j] = inf;
		}
	while (m--) {
		int x, y, a, b;
		in >> x >> y >> a >> b;
		cost[0][x][y] = a;
		cost[1][x][y] = b;
	}

	bt(0, 1, n, 0);
	bt(1, 1, n, 0);

	int rez = -1;

	for (auto itr : pos[0]) {
		if (pos[1][itr.first] == true) {
			rez = itr.first;
			break;
		}
	}
    if (rez == -1) {
		out << "IMPOSSIBLE";
	} else {
		out << rez << '\n';
	}
	return 0;
}
