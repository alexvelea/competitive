//Problem #A from Codeforces zepto
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN = 2005;

int t[kMaxN], h[kMaxN], m[kMaxN];

int n, x, mx;

vector<pair<int, int> > pq[2];
priority_queue<int> hp[2];

void solve() {
	sort(pq[0].begin(), pq[0].end());
	sort(pq[1].begin(), pq[1].end());

	int now = 0;
	int H = x;

	while (hp[0].size() != 0)
		hp[0].pop();
	while (hp[1].size() != 0)
		hp[1].pop();
	
 	int st[2];
	st[0] = st[1] = 0;

	while (true) {
	for (int t = 0; t < 2; ++t) {
 		for (int i = 0; i < 2; ++i) {
			while (st[i] < int(pq[i].size()) and pq[i][st[i]].first <= H) {
				hp[i].push(pq[i][st[i]].second);
				++st[i];
			}
		}   	
		
		if (hp[t].size() == 0) {
			if (mx < now)
				mx = now;
			return ;
		}
		int act = hp[t].top();
		hp[t].pop();
		H += act;
		++now;
	}
	}	
}

int main() {
	cin >> n >> x;
	for (int i = 1; i <= n; ++i) {
		cin >> t[i] >> h[i] >> m[i];
	}

	for (int i = 1; i <= n; ++i) {
		pq[t[i]].push_back(make_pair(h[i], m[i]));
	}
	
	solve();

	pq[0].clear();
	pq[1].clear();
	
	for (int i = 1; i <= n; ++i) {
		pq[t[i] ^ 1].push_back(make_pair(h[i], m[i]));
	}

	solve();

	cout << mx << '\n';

    return 0;
}

