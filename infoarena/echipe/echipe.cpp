//Problem echipe from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 255;

ifstream in("echipe.in");
ofstream out("echipe.out");

pair<int, int> seg[kMaxN];

int dp[kMaxN][kMaxN], Dp[kMaxN];

bool good[kMaxN];

int main() {
	int n, k; in >> n >> k;
	for (int i = 1; i <= n; ++i) {
		in >> seg[i].first >> seg[i].second;
	}

	sort(seg + 1, seg + n + 1);
	for (int i = n, mn = inf; i; --i) {
		if (seg[i].second >= mn) {
			good[i] = true;
		}
 		
		if (seg[i].second <= mn) {
			mn = seg[i].second;
		}
	}

	for (int i = 1; i <= n; ++i) {
		dp[i][0] = -inf;
		if (good[i] == true) {
			for (int K = 0; K <= k; ++K) {
				dp[i][K] = dp[i - 1][K];
			}
			continue;
		}
		for (int j = 1; j <= i; ++j) {
			if (good[j] == false) {
				for (int K = 1; K <= k; ++K) {
					dp[i][K] = max(dp[i][K], dp[j - 1][K - 1]  + (seg[j].second - seg[i].first));
				}
			}
		}
 		for (int K = 1; K <= k; ++K) {
			Dp[K] = dp[i][K];
		}
	}
 	
	vector<int> el;
    for (int i = 1; i <= n; ++i) {
		if (good[i] == true) {
			el.push_back(seg[i].second - seg[i].first);
		}
	}

	sort(el.begin(), el.end());
	reverse(el.begin(), el.end());
	
	int mx = 0;

	for (int i = k, j = 0, sum = 0; i; --i, ++j) {
		if (mx < Dp[i] + sum) {
			mx = Dp[i] + sum;
		}
		
		if (j < int(el.size())) {
			sum += el[j];
		}
	}

	el.clear();
	for (int i = 1; i <= n; ++i)
		el.push_back(seg[i].second - seg[i].first);
	sort(el.begin(), el.end());
	reverse(el.begin(), el.end());
 
	for (int sum = 0, i = 0; i + 1 < k or (k == n and i < k); ++i) {
		sum += el[i];
		if (sum >= mx) {
			mx = sum;
		}
	}

	out << mx << '\n';

	return 0;
}
