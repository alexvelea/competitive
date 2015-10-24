//Problem b @ 21-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxVal = 8005;

#define int64 long long

bool viz[kMaxVal];
bool dp[4][kMaxVal];

int main() {
	ios::sync_with_stdio(false);
    vector<int> primes;
    for (int i = 2; i < kMaxVal; ++i) {
        if (viz[i] == false) {
            primes.push_back(i);
            dp[0][i] = true;
            for (int j = i; j < kMaxVal; j += i) {
                viz[j] = true;
            }
        }
    }

    for (int p = 1; p < 4; ++p) {
        for (int a = 1; a < kMaxVal; a += 1) {
            if (dp[p - 1][a]) {
                for (auto itr : primes) {
                    if ((a | itr) < kMaxVal) {
                        dp[p][a | itr] = true;
                    }
                }
            }
        }
    }
    
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        cout << ((dp[3][x] == true) ? ("YES") : ("NO")) << '\n';
    }
	return 0;
}
