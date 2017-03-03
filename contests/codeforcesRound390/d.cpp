#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

vector<int> solution;
const int inf = 0x3f3f3f3f;

struct Coupon {
    int id, left, right;
    bool operator<(const Coupon& rhs) {
        return make_pair(left, right) < make_pair(rhs.left, rhs.right);
    }
};

int k;
vector<Coupon> all_coupons;

int GetMaxCount(int stop_at) {
    priority_queue<pair<int, int>> pq;
    int mx = 0;
    for (auto coupon : all_coupons) {
        pq.push({-coupon.right, coupon.id});
        if ((int)pq.size() == k + 1) {
            pq.pop();
        }

        if ((int)pq.size() != k) {
            continue;
        }

        int count = -pq.top().first - coupon.left + 1;
        if (count == stop_at) {
            while (pq.size()) {
                auto shit = pq.top();
                solution.push_back(shit.second);
                pq.pop();
            }

            return -1;
        }

        if (mx < count) {
            mx = count;
        }
    }

    return mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n >> k;
    for (int i = 0; i < n; i += 1) {
        int l, r; cin >> l >> r;
        all_coupons.push_back(Coupon({i, l, r}));
    }

    sort(all_coupons.begin(), all_coupons.end());
    int max = GetMaxCount(-2 * inf);
    GetMaxCount(max);
    if (max == 0) {
        cout << "0\n";
        for (int i = 1; i <= k; i += 1) {
            cout << i << ' ';
        }
    } else {
        cout << max << '\n';
        for (auto itr : solution) {
            cout << itr + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}

