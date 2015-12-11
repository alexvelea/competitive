//Problem D from Codeforces Round facebookHackerCup2015Round1
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

const int inf = 0x3f3f3f3f, kMaxN = 200005;

int start[4 * kMaxN], global[4 * kMaxN];

//ifstream in("input.txt");
//ofstream out("output.txt");

vector<int> vertex[kMaxN];
int st[kMaxN], dr[kMaxN];
void solve(int nod) {
//	cerr << nod << '\n';
	int sz = max(int(vertex[nod].size()), 1) + 1;

	for (int i = 0; i < sz; ++i)
		global[start[nod] + i] = 0;

	for (int itr : vertex[nod]) {
		solve(itr);
		int x = max(int(vertex[itr].size()), 1) + 1;
		st[0] = inf;
		dr[x - 1] = inf;
		for (int i = 1; i <= x; ++i) {
			st[i] = min(st[i - 1], global[start[itr] + i - 1]);
		}
		for (int i = x - 2; i >= 0; --i) {
			dr[i] = min(dr[i + 1], global[start[itr] + i + 1]);
		}
		for (int i = 0; i < x; ++i) {
			if (i < sz) {
				global[start[nod] + i] += min(st[i], dr[i]);
			}
			if (i + 1 < sz) {
				global[start[nod] + i + 1] -= min(st[i], dr[i]);
			}
		}
		if (x < sz)
			global[start[nod] + x] += st[x];
	}
	for (int i = 1; i < sz; ++i)
		global[start[nod] + i] += global[start[nod] + i - 1];
	for (int i = 0; i < sz; ++i)
 		global[start[nod] + i] += i + 1;
//	cerr << nod << "##\t";
//	for (int i = 0; i < sz; ++i)
//		cerr << global[start[nod] + i] << '\t';
//	cerr << '\n';
}

int main() {
 	int t;
	cin >> t;
	for (int T = 1; T <= t; ++T) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			int father;
			cin >> father;
			vertex[father].push_back(i);
		}
		start[1] = 1;
		for (int i = 2; i <= n; ++i) {
			start[i] = start[i - 1] + max(1, int(vertex[i - 1].size())) + 1;
		}
		solve(1);
        for (int i = 1; i <= n; ++i)
			vertex[i].clear();
		int rez = inf;
		for (int i = 1; i < start[2]; ++i)
			rez = min(rez, global[i]);
		if (n == 1)
			rez = 1;
		cout << "Case #" << T << ": " << rez << '\n';
//		cerr << "\n\n\n\n";
//		cerr << T << '\n';
	}
	return 0;
}
