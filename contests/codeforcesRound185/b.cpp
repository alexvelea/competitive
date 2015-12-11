#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT(it, v) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it)
#define mp make_pair
#define fi first
#define se second

const int INF = 0x3f3f3f3f, max_n = 100005;


int main() {
	freopen("test.txt","r",stdin);
    long long Sum[max_n];
	int n, m, p;
 	cin >> n >> m >> p;
	Sum[1] = 0;
	for (int i = 2; i <= n; ++i) {
		long long D;
		cin >> D;
		Sum[i] = Sum[i-1] + D;
	}
	vector<long long> nr;
	for (int i = 1; i <= m; ++i) {
		long long h, t;
		cin >> h >> t;
		t -= Sum[h];
 		nr.push_back(t);
	}
	sort (nr.begin(), nr.end());
	for (int i = 0; i < m; ++i)
		cerr << nr[i] << "#\n";
	cerr << "\n";
	long long Best[max_n], mn[max_n];
	Best[0] = 0;
	for (int i = 1; i < m; ++i) {
		Best[0] += nr[i] - nr[0];
	}
	for (int i = 1; i < m; ++i) {
		Best[i] = 1LL * INF * INF;
	}
	for (int P = 2; P <= p; ++P) {
		mn[0] = Best[0];
		for (int dr = 1; dr < m; ++dr) {
			mn[dr] = mn[dr-1];
			if (Best[dr] < mn[dr])
				mn[dr] = Best[dr];
		}
		int cost = 0;
		for (int dr = m-1; dr; --dr) {
			if (dr != m-1) {
				cost += ( nr[dr+1] - nr[dr] ) * ( m - 1 - dr);
			}
			cerr << dr << "\t" << cost << "\t" << mn[dr] << "\n";
			if (Best[dr] > cost + mn[dr-1])
				Best[dr] = cost + mn[dr-1];
		}
	}
	int mx = Best[0];
	for (int dr = 0; dr < m; ++dr)
		if (mx > Best[dr])
			mx = Best[dr];
	cout << mx << "\n";
	return 0;
}
