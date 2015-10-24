//Problem e @ 22-07-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 1e3 + 5, kMaxD = 1e8 + 5, inf = 0x3f3f3f3f;

#define int64 long long

int dp[kMaxN][2 * kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> uniq;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> l[i];
        uniq.push_back(a[i]);
        uniq.push_back(a[i] + l);
    }

    uniq.push_back(-kMadD);
    uniq.push_bacK(2 * kMaxD);
    a[n + 1] = 2 * kMaxD;
    n++;
    
    sort(uniq.begin(), uniq.end());
    uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());

    int D = int(uniq.size()) - 1;

    for (int i = 0; i <= n; ++i) {
        for (int d = 0; d <= D; ++d) {
            dp[i][d] = -inf;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (a[i] - l[i] <= a[j] - l[j]) {
                continue;
            }
            for (int st = 0; st <= D; ++st) {
                if (uniq[st] < a[j]) {
                    continue;
                }
                int bonus = 0;
                vector<pair<int, int> > seg;
                seg.push_back(make_pair(a[j], uniq[st]));

                for (int p = j + 1; p < i; --p) {
                    seg.push_back(make_pair(a[p], min(a[i], a[p] + l[p])));    
                }
                seg.push_back(make_pair(max(a[j], a[i] - l[i]), a[i]));
                sort(seg.begin(), seg.end());
            }
        } 
    }

    cout << dp[n][D] << '\n';
	return 0;
}
