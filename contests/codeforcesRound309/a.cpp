//Problem a @ 25-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1005, kMod = 1000000007;
const double eps = 1e-7;

#define int64 long long

int sum[kMaxN], el[kMaxN];
int comb[kMaxN][kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> el[i];
        sum[i] = sum[i - 1] + el[i];
    }
    comb[1][1] = 1;
    for (int i = 1; i <= 1000; ++i) {
        comb[0][i] = comb[i][0] = 1;
    }
    
    for (int i = 2; i <= 1000; ++i) {
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            comb[i][j] %= kMod;
        }
    }

    int rez = 1;
    for (int i = n; i > 1; --i) {
        rez = (1LL * rez * comb[sum[i] - 1][el[i] - 1]) % kMod;
    }
    cout << rez << '\n';
	return 0;
}
