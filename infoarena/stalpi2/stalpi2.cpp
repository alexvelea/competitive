#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("stalpi2.in");
ofstream out("stalpi2.out");

const int inf = 0x3f3f3f3f, kMaxN = 55, kMaxD = 10005;

int n, e, el[kMaxN], dp[kMaxD], dpNew[kMaxD];
int deq[kMaxD];

bool solve(int d) {
	for (int i = 0; i < kMaxD; ++i)
		dp[i] = e + 1;
	for (int i = 0; i <= d; ++i)
		dp[i] = abs(i - el[1]);
	for (int i = 2; i < n; ++i) {
		int st = 1;
		int dr = 0;
		dpNew[1] = e + 1;
		for (int j = 0; j <= el[n]; ++j) {
			if (st <= dr and j - deq[st] > d)
				++st;
			while (dr >= st and dp[deq[dr]] >= dp[j])
				--dr;
			deq[++dr] = j;
			dpNew[j] = dp[deq[st]] + abs(j - el[i]);
			if (dpNew[j] > e)
				dpNew[j] = e + 1;
		}
		for (int j = 1; j <= el[n]; ++j)
			dp[j] = dpNew[j];
	}
	for (int i = el[n]; el[n] - i <= d; --i)
		if (dp[i] <= e)
			return true;
	return false;
}

int main() {
	in >> n >> e;
	n--;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	int rez = 0, p = 1024 * 8;
	for (; p; p>>=1)
		if (not solve(p + rez))
			rez += p;
	out << rez + 1 << '\n';
	return 0;
}
