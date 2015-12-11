//Problem #C from Codeforces 237
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int kMaxN = 100005;

vector<int> el[kMaxN];
vector<pair<int, int> > sol;
pair<int, int> d[kMaxN];
int remaining[kMaxN];

int main() {
	int n, k;
	cin >> n >> k;
	k--;
	for (int i = 1; i <= n; ++i)
		remaining[i] = k;
	for (int i = 1; i <= n; ++i) {
		cin >> d[i].first;
		d[i].second = i;
		el[d[i].first].push_back(i);
	}
	sort(d + 1, d + n + 1);
	int start = d[1].second;
	remaining[start]++;
	bool ok = true;

	if (d[1].first != 0)
		ok = false;

	for (int i = 2; i <= n and ok; ++i) {
		int cost = d[i].first;
		if (cost == 0) {
			ok = false;
			break;
		}
		
		while (el[cost - 1].size() and remaining[el[cost - 1].back()] == 0) {
			el[cost - 1].pop_back();
		}
		if (el[cost - 1].size() == 0) {
			ok = false;
			break;
		}
		int nod = el[cost - 1].back();
		remaining[nod]--;
		sol.push_back(make_pair(nod, d[i].second));
	}
	if (ok == false) {
		cout << "-1\n";
	} else {
		cout << n - 1 << '\n';
		for (int i = 0; i < int(sol.size()); ++i)
			cout << sol[i].first << ' ' << sol[i].second << '\n';
	}
    return 0;
}

