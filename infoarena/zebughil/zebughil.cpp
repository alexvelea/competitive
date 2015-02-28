#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long
const int kMaxN = 17;

ifstream in("zebughil.in");
ofstream out("zebughil.out");

int n;
int64 g, el[kMaxN];
pair<int, int64> DP[1 << kMaxN];

pair<int, int64> add(pair<int, int64> a, int64 b) {
	if (a.second + b > g) {
		a.second = b;
		a.first++;
	} else {
		a.second += b;
	}
	return a;
}

void get_min(pair<int, int64> &a, pair<int, int64> b) {
	if (a.first > b.first)
		a = b;
	if (a.first == b.first and a.second > b.second)
		a = b;
}

void solve() {
	DP[0] = make_pair(0, 0);
	for (int i = 1; i < (1 << n); ++i) {
		DP[i] = make_pair(n, 0);
		for (int j = 0; j < n; ++j)
			if (i & (1 << j))
				get_min(DP[i], add(DP[i ^ (1 << j)], el[j]));
	}
}

int main() {
	while (in >> n) {
		in >> g;
		for (int i = 0; i < n; ++i)
			in >> el[i];
 		solve();
		out << 1 + DP[(1 << n) - 1].first << '\n';
	}
	return 0;
}
