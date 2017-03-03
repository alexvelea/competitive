#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxK = 1e3+5, kMaxN = 1e4+5;

long double dp[kMaxK][kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    int k, q; cin >> k >> q;
    dp[0][0] = 1.0;
    int max_n = kMaxN;
    for (int l = 1; l < max_n; l += 1) {
        for (int el = 1; el <= k; el += 1) {
            dp[el][l] = el * dp[el][l - 1] + (k - el + 1) * dp[el - 1][l - 1];
            dp[el][l] /= k;
        }
    }

    for (int i = 0; i < q; i += 1) {
        double p; cin >> p;
        for (int j = 0; ; j += 1) {
            if (dp[k][j] * 2000.0 > p - 1e-9) {
                cout << j << '\n';
                break;
            }
        }
    }
    return 0;
}
