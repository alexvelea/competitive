#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("meciul.in");
ofstream out("meciul.out");

const int kMaxN = 500005;

bool viz[kMaxN], color[kMaxN];
int a[kMaxN], b[kMaxN];

vector<int> vertex[kMaxN];

bool df(int nod, int &m) {
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		if (itr > m)
			continue;
		int oth = a[itr] + b[itr] - nod;
		if (not viz[oth]) {
			color[oth] = 1 ^ color[nod];
			if (not df(oth, m))
				return false;
		} else {
			if (color[nod] == color[oth])
				return false;
		}
	}
	return true;
}

bool check(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		viz[i] = false;
	}
	for (int i = 1; i <= n; ++i) {
		if (not viz[i]) {
			if (not df(i, m))
				return false;
		}
	}
	return true;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, m;
		in >> n >> m;
		for (int i = 1; i <= n; ++i) {
			vertex[i].clear();
		}

		for (int i = 1; i <= m; ++i) {
			in >> a[i] >> b[i];
			vertex[a[i]].push_back(i);
			vertex[b[i]].push_back(i);
		}
		int l = 1, rez = 0;
		while (l < m)
			l *= 2;
		for (; l; l /= 2) {
			if (rez + l <= m) {
				if (check(n, rez + l))
					rez += l;
			}
		}
		for (int i = 1; i <= rez; ++i) {
			out << "YES\n";
		}
		for (int i = rez + 1; i <= m; ++i) {
			out << "NO\n";
		}
	}
	return 0;
}
