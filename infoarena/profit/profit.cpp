//Problem profit from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 2005;

ifstream in("profit.in");
ofstream out("profit.out");

int el[kMaxN], r[kMaxN];
int n, rez = inf;

vector<int> uniq;
int dp[kMaxN];

void solve() {
	for (int i = 1; i <= n; ++i)
		dp[i] = inf;

	for (int i = 0; i < int(uniq.size()); ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[j] = min(dp[j], dp[j - 1] + abs(el[j] - uniq[i]));
		}
	}
 	
	if (rez > dp[n])
		rez = dp[n];
	return ;
}

int main() {
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
	}


	for (int i = 1; i <= n; ++i) {
		uniq.push_back(el[i]);
	}

	sort(uniq.begin(), uniq.end());
	uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());

	solve();
	reverse(el + 1, el + n + 1);
	solve();

    out << rez << '\n';
	return 0;
}
