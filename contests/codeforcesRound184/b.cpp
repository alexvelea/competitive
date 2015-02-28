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
#define INF 0x3f3f3f3f


long long el[100];
long long a, b, n, down, up;
int i;

long long gcd (long long a, long long b) {
	if (b == 0)
		return a;
	return gcd (b, a%b);
}
int main() {
 	cin >> a >> b;
	cin >> n;
	for (i=1; i<=n; ++i) {
		cin >> el[i];
	}
	up = 1;
	down = 0;
	bool ok = true;
	long long mx = max (a, b);
	for (i=n; i; --i) {
		swap (up, down);
		if ((mx-up)/el[i] < 1LL*(down-1))
			ok = false;
 		up += 1LL*down*el[i];
	}
 	long long d = gcd (a,b);
	a /= d;
	b /= d;
	d = gcd (up, down);
 	up /= d;
	down /= d;
 	if (ok && a == up && b == down) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}
