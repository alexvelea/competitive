//Problem d if from hackerrank101Hack23
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 505, kMod = 1000000009;

bool viz[kMaxN], bad[kMaxN], ok;
int father[kMaxN], m, nrBad, deep[kMaxN];

vector<int> vertex[kMaxN];

void solve(int nod) {
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		if (viz[itr] == false) {
			father[itr] = nod;
			deep[itr] = deep[nod] + 1;
			solve(itr);
		} else {
			if (father[nod] != itr and deep[nod] > deep[itr]) {
				// mergem in sus
				for (int i = nod; i != father[itr]; i = father[i]) {
					if (bad[i] == true) {
						ok = false;
					}
					bad[i] = true;
					--m;
					nrBad++;
				}
				nrBad--;
			}
		}
	}
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		ok = true;
		nrBad = 0;

		int n; cin >> n >> m;
		for (int i = 1; i <= m; ++i) {
			int a, b; cin >> a >> b;
			vertex[a].push_back(b);
			vertex[b].push_back(a);
		}
		for (int i = 1; i <= n; ++i) {
			if (not viz[i]) {
				solve(i);
			}
		}
		cerr << nrBad << '\t' << m << '\n';
		m = max(0, m - 1);
		nrBad += m;
		int rez = 1;
		while (nrBad) {
			rez = (rez + rez) % kMod;
			nrBad--;
		}

		rez *= ok;
		cout << rez << '\n';
		

		for (int i = 1; i <= n; ++i) {
			viz[i] = false;
			father[i] = 0;
			bad[i] = false;
			vertex[i].clear();
		}
	}
	return 0;
}
