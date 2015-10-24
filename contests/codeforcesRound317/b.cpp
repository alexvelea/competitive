//Problem b @ 22-08-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxK = 5e3 + 5;

#define int64 long long

int64 dp[kMaxK][kMaxK];
int64 sum[int(3e5 + 5)];

void getMin(int64 &a, int b) {
    if (a > b) {
        a = b;
    }
}

int main() {
	ios::sync_with_stdio(false);
    int n, k; cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> sum[i];
    }
    sort(sum + 1, sum + n + 1);

    vector<int> values = {n / k, (n + k - 1) / k}, howMany = {k - (n % k), n % k};
    int a = howMany[0];
    int b = howMany[1];
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            dp[i][j] = 1LL * inf * inf;
        }
    }
//    cerr << values[0] << '\t' << howMany[0] << '\t' << values[1] << '\t' << howMany[1] << '\n';
    dp[0][0] = 0;
    
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (i == 0 and j == 0) {
                continue;
            }
            
            if (i) {
                // punem mica
                int now = i * values[0] + j * values[1];
                int late = now - values[0] + 1;
                getMin(dp[i][j], dp[i - 1][j] + sum[now] - sum[late]);
            }

             if (j) {
                // punem mare
                int now = i * values[0] + j * values[1];
                int late = now - values[1] + 1;
                getMin(dp[i][j], dp[i][j - 1] + sum[now] - sum[late]);
            }
//            cerr << i << '\t' << j << '\t' << dp[i][j] << '\n';
        }
    }

    cout << dp[a][b] << '\n';
	return 0;
}
