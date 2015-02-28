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
 	long long a, b;
	cin >> a >> b;
	for (int i = 63; i>=0; --i) {
		if ((a&(1LL<<i)) != (b&(1LL<<i))) {
			cout << (1LL<<i) - 1 + (1LL<<i) << "\n";
			return 0;
		}
	}
	cout << "0\n";
	return 0;
}
