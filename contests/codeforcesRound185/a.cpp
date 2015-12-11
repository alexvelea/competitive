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

const int INF=0x3f3f3f3f;

int main() {
	int n, k;
 	cin >> n >> k;
	// asdasdsa
	if ( k < n*(n-1)/2) {
		for (int i = 1; i <= n; ++i)
			cout << 1 << " " << i << "\n";
	} else {
		cout << "no solution\n";
	}
 	return 0;
}
