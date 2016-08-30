#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define int64 long long

const int kMaxN = 1e5+5;
const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int64> sums(2 * n, 0);
    for (int i = 0; i < n; i += 1) {
        cin >> sums[i];
        sums[n + i] = sums[i];
    }

    for (int i = 1; i < 2 * n; i += 1) {
        sums[i] += sums[i - 1];
    }

    unordered_map<int64, int> cnt;
    for (int i = 0; i < n; i += 1) {
//        cerr << "Add\t" << sums[i] << '\n';
        cnt[sums[i]] += 1; 
    }

    int ans = 0;

    for (int i = 0; i < n; i += 1) {
        ans = max(ans, cnt[sums[i]]);
        if (i + 1 != n) {
//            cerr << "remove\t" << sums[i] << '\n';
//            cerr << "Add\t" << sums[i + n] << '\n';
            cnt[sums[i]] -= 1;
            cnt[sums[i + n]] += 1;
        }
    }

    cout << n - ans;
    return 0;
}
