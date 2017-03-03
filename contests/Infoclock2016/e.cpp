#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

const int kMaxN = 2e5+5;

int element[kMaxN];

struct Solution {
    pair<int, int> mn;
    pair<int, int> mx;

    Solution() : mn({+inf, 0}), mx({-inf, 0}) { }
    Solution(pair<int, int> mn, pair<int, int> mx) : mn(mn), mx(mx) { }

    Solution Merge(const Solution& rhs) {
        Solution s;
        s.mn = min(mn, rhs.mn);
        s.mx = max(mx, rhs.mx);
        return s;
    }
} aint[4 * kMaxN];

void MakeAint(int node, int left, int right) {
    if (left == right) {
        aint[node] = Solution(make_pair(element[left], left), make_pair(element[left], left));
        return;
    }

    int mid = (left + right) / 2;
    MakeAint(2 * node, left, mid);
    MakeAint(2 * node + 1, mid + 1, right);
    aint[node] = aint[2 * node].Merge(aint[2 * node + 1]);
}

Solution Query(int node, int left, int right, int c1, int c2) {
    if (c2 < left or right < c1) {
        return Solution();
    }

    if (c1 <= left and right <= c2) {
        return aint[node];
    }
    
    int mid = (left + right) / 2;
    auto a = Query(2 * node, left, mid, c1, c2);
    auto b = Query(2 * node + 1, mid + 1, right, c1, c2);
    return a.Merge(b);
}


int main() {
    ios_base::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i += 1) {
        cin >> element[i];
    }

    MakeAint(1, 1, n);

    while (q--) {
        int l, r, v; cin >> l >> r >> v;
        auto s = Query(1, 1, n, l, r);
        if (s.mn.first == s.mx.first and s.mn.first == v) {
            cout << "-1\n";
        } else {
            if (s.mn.first != v) {
                cout << s.mn.second << '\n';
            } else {
                cout << s.mx.second << '\n';
            }
        }
    }

    return 0;
}

