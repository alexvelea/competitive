//Problem b @ 15-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int kMod = 1e9 + 7;

#define int64 long long

map<int, int> under, ap;

int w[int(1e6 + 6)];

int main() {
	ios::sync_with_stdio(false);
    int n, k; int64 l; cin >> n >> l >> k;
    vector<int> event;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        event.push_back(w[i]);
    }
    sort(event.begin(), event.end());
    for (int i = 0; i < int(event.size()); ++i) {
        under[event[i]] = i + 1;
        ap[event[i]] += 1;
    }
    event.resize(unique(event.begin(), event.end()) - event.begin());

    int64 R = l % kMod;

    int extra = l % n;

    for (int x = 2; n <= l and x <= k; ++x) {
        if (extra and 1LL * (x - 1) * n + extra <= l) {
            for (int i = 1; i <= extra; ++i) {
                R += under[w[i]]; 
                R %= kMod;
            }
        }

        if (1LL * x * n <= l) {
            int64 bonus = (l - 1LL * (x - 1) * n) / n;
            bonus = bonus % kMod;
            for (int i = 1; i <= n; ++i) {
                R += 1LL * bonus * under[w[i]];
                R %= kMod;
            }
        }
    
        int64 now = 0;
        for (auto itr : event) {
            now = 1LL * (now + 1LL * ap[itr] * under[itr]) % kMod;
            under[itr] = now;
        }
    }
    cout << R << '\n';
    return 0;
}
