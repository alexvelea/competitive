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

const int INF=0x3f3f3f3f;

int main() {
	int n, k;
	cin >> n >> k;
	bool set = false;
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		int f, t;
		cin >> f >> t;
		if (f -  max(0, t-k) > mx || !set) {
			set = true;
			mx = f - max(0, t-k);
		}
	}
	cout << mx << "\n";
	return 0;
}                                                                                            
