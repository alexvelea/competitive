//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("marsmusic.in");
ofstream out("marsmusic.out");

const int inf = 0x3f3f3f3f;

double rez = 0.0;
int sum, n;

double dp[55][10005];
int val[55], fact[55];

void solve(int now) {
	for (int itr = 0; itr <= n; ++itr) 
		for (int i = 0; i <= sum; ++i)
			dp[itr][i] = 0.0;
	dp[0][0] = 1.0;
	for (int i = 1; i <= n; ++i) {
		if (i == now)
			continue;
 		for (int j = n; j >= 1; --j)
			for (int s = 0; s + val[i] <= sum; ++s)
				dp[j][s + val[i]] += dp[j - 1][s];
	}

	for (int a = 0; a < n; ++a)
		for (int b = 0; b < n; ++b)
			for (int i = 0; i <= sum - val[now]; ++i)
				for (int j = max(0, i - val[now]); j <= min(sum - val[now], i + val[now]); ++j) {
					int a = min(i, j);
					int b = max(i, j);
					rez += dp[a][i] * dp[b][j] * fact[a] * fact[b] * fact[n - a - 1] * fact[n - b - 1] * max(0, val[now] + b - a);
				}
}	


int main() {
	fact[0] = 1.0;
	for (int i = 1; i <= 50; ++i)
		fact[i] = fact[i - 1] * i;
	in >> sum >> n;
	for (int i = 1; i <= n; ++i)
		in >> val[i];
	
	for (int i = 1; i <= n; ++i)
    	solve(i);

	rez /= fact[n];
	rez /= fact[n];
	out << fixed << setprecision(8) << rez << '\n';
    return 0;
}
