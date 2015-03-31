//Problem cover from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxL = 1000005;

ifstream in("cover.in");
ofstream out("cover.out");

int cost[kMaxL], dp[kMaxL], deq[kMaxL], segmentBegin[kMaxL];

void getMax(int &a, int b) {
	if (a < b) {
		a = b;
	}
}

int main() {
	int n, l; in >> n >> l;
	for (int i = 1; i <= l; ++i) {
		in >> cost[i];
	}
	
	for (int i = 1; i <= n; ++i) {
		int st, dr; in >> st >> dr;
		getMax(segmentBegin[dr], st);
	}

	dp[0] = 0;
	int dr = 0, st = 1;
	deq[++dr] = 0;

	for (int i = 1; i <= l + 1; ++i) {
   		dp[i] = cost[i] + dp[deq[st]];
		while (dr >= st and dp[deq[dr]] >= dp[i]) {
			--dr;
		}
		deq[++dr] = i;
		while (deq[st] < segmentBegin[i]) {
			++st;
		}
	}
 	out << dp[l + 1] << '\n';
	return 0;
}
