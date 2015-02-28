//Problem B from Codeforces Round 286
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

const int inf = 0x3f3f3f3f;

vector<int> vertex[105][105];

bool viz[105];

void df(int nod, int c) {
	viz[nod] = true;
	for (int itr : vertex[c][nod]) {
		if (not viz[itr])
			df(itr, c);
	}
}

int main() {
	int n, m;
    cin >> n >> m;
	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;
		vertex[c][a].push_back(b);
		vertex[c][b].push_back(a);
	}

	int q;
	cin >> q;
	while (q--) {
		int a, b, rez = 0;
		cin >> a >> b;
		for (int i = 1; i <= 100; ++i) {
			for (int j = 1; j <= n; ++j)
				viz[j] = false;
			df(a, i);
			rez += viz[b];
		}
		cout << rez << '\n';
	}
	
	return 0;
}
