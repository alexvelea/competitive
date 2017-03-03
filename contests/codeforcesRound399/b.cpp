#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

typedef long long int64;

struct S {
    int64 ones_inside;
    int64 len;
};

map<int64, S> cache;

S Get(int64 n) {
    if (cache.find(n) != cache.end()) {
        return cache[n];
    }
     
    S s;
    if (n < 2) {
        s.len = 1;
        s.ones_inside = n;
        cache[n] = s;
        return s;
    }

    S s2 = Get(n / 2);
    s.len = 2 * s2.len;
    s.ones_inside = 2 * s2.ones_inside;
    s.len += 1;
    s.ones_inside += n & 1;
    cache[n] = s;
    return s;
}

int64 Solve(int64 n, int64& pos) {
    S s = Get(n);
    if (pos <= 0) {
        return 0;
    }

    if (s.len <= pos) {
        pos -= s.len;
        return s.ones_inside;
    }

    int64 ans = 0;

    for (auto itr : {(n / 2), (n & 1), (n / 2)}) {
        if (pos <= 0) {
            return ans;
        }

        auto s2 = Solve(itr, pos);
        ans += s2;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    int64 n, l, r; cin >> n >> l >> r;

    int64 R = Solve(n, r);
    l -= 1;
    int64 L = Solve(n, l);

    cout << R - L << '\n';
    return 0;
}
