//Problem chomp from Infoarena
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

const int inf = 0x3f3f3f3f, kMod = 334214459, kMaxN = 130;

ifstream fin("chomp.in");
ofstream fout("chomp.out");

void mod(int &a) {
	if (a >= kMod) {
		a -= kMod;
	}
}

int dp[kMaxN][kMaxN];

int main() {
	int t; fin >> t;
	for (int l = 1; l <= 128; ++l) {
		dp[l][0] = 1;
		for (int c = 1; c <= 128; ++c) {
			dp[l][c] = dp[l - 1][c] + dp[l][c - 1];
			mod(dp[l][c]);
		}
	}

 	for (int l = 1; l <= 128; ++l) {
		for (int c = 1; c <= 128; ++c) {   
			dp[l][c] += dp[l][c - 1];
			mod(dp[l][c]);
		}
	}

	while (t--) {
		int x, y; fin >> x >> y;
		fout << dp[x][y] << '\n';
	}
	return 0;
}
