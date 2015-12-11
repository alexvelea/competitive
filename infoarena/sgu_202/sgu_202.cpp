//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

unsigned long long dp[70][70];
int where[70][70];

int main() {
	// prepare the DP
	for (int i = 1; i <= 64; ++i) {
		dp[i][3] = (1LL << (i - 1)) - 1;
		dp[i][3] += (1LL << (i - 1));
	}

	for (int j = 4; j <= 64; ++j) {
		for (int i = 1; i <= 64; ++i) {
			dp[i][j] = dp[64][3];
			for (int l = 0; l < min(63, i); ++l) {
				if (2 * dp[l][j - 1] + dp[i - l][j - 1] < dp[i][j]) {
					dp[i][j] = 2 * dp[l][j - 1] + dp[i - l][j - 1];
					where[i][j] = l;
				}
			}
		}
	}
    
	in >> n >> m;
	
	return 0;
}
