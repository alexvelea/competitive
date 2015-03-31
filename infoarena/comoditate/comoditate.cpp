//Problem comoditate from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("comoditate.in");
ofstream out("comoditate.out");

struct Edge {
	int x, y;
	bool type, isSet;
    Edge(int _x, int _y) {
		type = isSet = false;
		x = _x;
		y = _y;
	}

	Edge() {
		x = y = type = isSet = 0;
	}

	void set(int nod) {
		if (isSet) {
			return ;
		}
		type = (nod == y);
		isSet = true;
	}
	
	int other(int nod) {
		return x + y - nod;
	}
} edge[kMaxN];

bool viz[kMaxN];
vector<int> vertex[kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		edge[itr].set(nod);
		if (not viz[edge[itr].other(nod)]) {
			df(edge[itr].other(nod));
		}
	}
}

int main() {
	int t; in >> t;
	while (t--) {
		int n, m; in >> n >> m;
		for (int i = 1; i <= m; ++i) {
			int x, y; in >> x >> y;
			if (x > y) {
				swap(x, y);
			}
			edge[i] = Edge(x, y);

			vertex[x].push_back(i);
			vertex[y].push_back(i);
		}

		df(1);
		for (int i = 1; i <= m; ++i) {
			out << edge[i].type;
		}
		out << '\n';
		
		for (int i = 1; i <= n; ++i) {
			viz[i] = false;
			vertex[i].clear();
		}
	}
	return 0;
}
