#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

class PickAndDelete {
public:
	#define mod 1000000007
	int pow(int a, int p) {
		int rez = 1;
		while (p) {
			if (p & 1)
				rez = (1LL * rez * a) % mod;
			a = (1LL * a * a) % mod;
			p >>= 1;
		}
		return rez;
	}

    int count( vector <string> S )  {
    	string s = "";
		for (int i = 0; i < int(S.size()); ++i)
			s += S[i];
		istringstream in(s);
 		int el;
		vector<int> nr;
		nr.push_back(0);
		while (in >> el)
			nr.push_back(el);
 		int dp[205][205], comb[205][205];

		for (int i = 0; i < 205; ++i)
			comb[i][0] = 1;
		for (int i = 1; i < 205; ++i)
			for (int j = 1; j <= i; ++j) {
				comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
				if (comb[i][j] >= mod)
					comb[i][j] -= mod;
			}
		sort(nr.begin(), nr.end());
		int n = nr.size() - 1;
		dp[0][0] = 1;
 		for (int i = 1; i <= n; ++i) {
			for (int st = 0; st <= i; ++st) {
				for (int start = 1; start <= st + 1; ++start) {
					dp[i][start] += (1LL * ((1LL * dp[st][start - 1] * (comb[n - st][i - st])) % mod) * pow(nr[start] - nr[start - 1], i - st)) % mod;
					while (dp[i][start] >= mod)
						dp[i][start] -= mod;
				}
			}
		}
		return dp[n][n];
	}
};



// Powered by FileEdit
// Powered by moj 4.17 [modified TZTester]
// Powered by CodeProcessor
