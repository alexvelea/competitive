#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("cuvant.in");
ofstream out("cuvant.out");

const int kMaxN = 10005, Mod = 666013;

string txt;
int ap[26];
int dp[1005];

int comb[1005][1005];

int main() {
	for (int i = 1; i <= 1000; ++i)
		comb[i][i] = comb[i][0] = 1;
	for (int i = 2; i <= 1000; ++i)
		for (int j = 1; j < i; ++j) {
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
			if (comb[i][j] >= Mod)
				comb[i][j] -= Mod;
		}
	
	int t;
	in >> t;
	while (t--) {
		in >> txt;
		int l;
		in >> l;
		
		for (int i = 0; i < 26; ++i)
			ap[i] = 0;
		
		for (int i = 0; i < int(txt.size()); ++i)
			ap[txt[i] - 'a']++;

 		for (int i = 1; i <= 1000; ++i)
			dp[i] = 0;

		dp[0] = 1;
		for (int i = 0; i < 26; ++i) {
			for (int x = l; x >= 0; --x) {
				for (int y = 1; y <= (l - x) and y <= ap[i]; ++y) {
					dp[x + y] = (1LL * dp[x] * comb[l - x][y] + dp[x + y]) % Mod;
				}
			}
		}
		out << dp[l] << '\n';
	}
    return 0;
}
