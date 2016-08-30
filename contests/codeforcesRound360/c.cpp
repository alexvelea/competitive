#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;

const int kMaxN = 505;

int cost[kMaxN];
int dp[kMaxN][kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i += 1) {
        cin >> cost[i];
    }

    dp[0][0] = true;
    for (int i = 0; i < n; i += 1) {
        for (int a = k; a >= 0; a -= 1) {
            for (int b = k; b >= 0; b -= 1) {
                if (dp[a][b] == false) {
                    continue;
                }

                if (a + cost[i] <= k and b + cost[i] <= k) {
                dp[min(a + cost[i], k)][min(b + cost[i], k)] = true;
                }
                if (b + cost[i] <= k) {
                dp[a][min(b + cost[i], k)] = true;
                }
            }
        }
    }

    vector<int> result;
    for (int i = 0; i <= k; i += 1) {
    if (dp[i][k]) {
        result.push_back(i);
    }}

    cout << result.size() << '\n';
    for (auto itr : result) {
        cout << itr << ' ';
    }

    return 0;
}
