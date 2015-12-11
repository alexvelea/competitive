//Problem D from Codeforces Round 292
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

bool viz[kMaxN];
int64 down[kMaxN], up[kMaxN], rez[kMaxN];
vector<pair<int, int> > vertex[kMaxN];

void dfDown(int nod) {
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		if (not viz[itr.first]) {
			dfDown(itr.first);
			down[nod] = max(down[nod], down[itr.first] + itr.second);
		}
	}
}

void dfUp(int nod) {
	viz[nod] = true;
	int64 a = up[nod], b = 0;
	for (auto itr : vertex[nod]) {
		if (not viz[itr.first]) {
			int64 c = down[itr.first] + itr.second;
			if (c > a) {
				b = a;
				a = c;
			} else {
				if (c > b) {
					b = c;
				}
			}
		}
	}
	rez[nod] = max(down[nod], up[nod]);

	for (auto itr : vertex[nod]) {
		if (not viz[itr.first]) {
			int64 c = down[itr.first] + itr.second;
			if (a == c) {
				c = b + itr.second;
			} else {
				c = a + itr.second;
			}
			up[itr.first] = c;
			dfUp(itr.first);
		}
	}
	return ;
}


int main() {
	int n;
	ios::sync_with_stdio(false);
    cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		int cost;
		cin >> a >> b >> cost;
		vertex[a].push_back(make_pair(b, cost));
 		vertex[b].push_back(make_pair(a, cost));   	
	}

	dfDown(1);
	for (int i = 1; i <= n; ++i) {
		viz[i] = false;
	}
	dfUp(1);
	vector<int64> bsearch(n + 1);
	for (int i = 1; i <= n; ++i) {
		cerr << i << '\t' << rez[i] << '\n';
		bsearch[i - 1] = rez[i];
	}
 	bsearch[n] = 1LL * inf * inf;
	sort(bsearch.begin(), bsearch.end());
	for (auto itr : bsearch) {
		cerr << itr << '\t';
	}
	cerr << '\n';
	int m;
	cin >> m;
	for (int i = 1; i <= m; ++i) {
        int64 l;
		cin >> l;
		l += bsearch[0];
		int poz = upper_bound(bsearch.begin(), bsearch.end(), l) - bsearch.begin();
		cout << poz << '\n';
	}

	return 0;
}
