#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, kMaxN = 4e5+1, kMod = 1e9+7;

int pow(int a, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res = 1LL * res * a % kMod;
        }
        a = 1LL * a * a % kMod;
        p /= 2;
    }

    return res;
}

int fact[kMaxN], invFact[kMaxN + 1];

int comb(int a, int b) {
    if (a < b) {
        return 0;
    }

    return 1LL * fact[a] * invFact[b] % kMod * invFact[a - b] % kMod;
}

int main() {
    fact[0] = fact[1] = invFact[0] = invFact[1] = 1;
    for (int i = 2; i < kMaxN; i += 1) {
        fact[i] = 1LL * fact[i - 1] * i % kMod;    
    }

    invFact[kMaxN - 1] = pow(fact[kMaxN - 1], kMod - 2);

    for (int i = kMaxN - 2; i >= 1; i -= 1) {
        invFact[i] = 1LL * invFact[i + 1] * (i + 1) % kMod;
    }

    ios_base::sync_with_stdio(false);
    int n, k; cin >> n >> k;

    vector<pair<int, int>> point(n);
    vector<int> uniq;
    for (int i = 0; i < n; i += 1) {
        int x, y; cin >> x >> y;
        point[i] = {x, y};
        uniq.push_back(x);
        uniq.push_back(y + 1);
    }

    sort(uniq.begin(), uniq.end());
    uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());

    vector<int> partial_sums(uniq.size(), 0);
    for (auto itr : point) {
        partial_sums[
            lower_bound(uniq.begin(), uniq.end(), itr.first) - uniq.begin()
        ] += 1;

        partial_sums[
            lower_bound(uniq.begin(), uniq.end(), itr.second + 1) - uniq.begin()
        ] -= 1;
    }

    int last = 0;
    for (auto& itr : partial_sums) {
        itr += last;
        last = itr;
    }

    int64 result = 0;
    for (int i = 0; i + 1 < (int)partial_sums.size(); i += 1) {
        result += 1LL * comb(partial_sums[i], k) * (uniq[i + 1] - uniq[i]);
        result %= kMod;
    }
    cout << result << '\n';
    return 0;
}
