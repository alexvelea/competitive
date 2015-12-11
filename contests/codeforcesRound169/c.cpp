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
#define th third

const int INF=0x3f3f3f3f, max_n = 200005;

int main() {
	int n, q;
	cin >> n >> q;
	int El[max_n];
	for (int i = 1; i <= n; ++i) 
		cin >> El[i];
	int Ap[max_n];
	for (int i = 0; i < max_n; ++i) 
		Ap[i] = 0;
	for (int i = 1; i <= q; ++i) {
		int l, r;
		cin >> l >> r;
		Ap[l]++;
		Ap[r+1]--;
	}
 	for (int i=1; i<=n; ++i) {
		Ap[i] += Ap[i-1];
	}
	sort (Ap+1, Ap+n+1);
	sort (El+1, El+n+1);
	long long sum = 0;
 	for (int i = 1; i <= n; ++i) {
		sum += 1ll * Ap[i] * El[i];
	}
	cout << sum << "\n";
	return 0;
}
