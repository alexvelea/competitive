#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define ll long long
const int max_n = 100005;

ll h[max_n], query[max_n];
int n, m;

bool solve (ll p) {
    int st = 1;
    for (int i = 1; i <= n; ++i) {
        if (st == m + 1)
            return true;
        // mergem de la h[i]
        if (h[i] >= query[st]) {
            if (h[i] - p > query[st])
                return false;
            ll mx = 1LL * h[i] + 1LL * (p - h[i] + query[st]) / 2;
            mx = max(mx, 1LL * (h[i] + (p - 2 * (h[i] - query[st]))));
            while (st <= m && query[st] <= mx)
                ++st;
        } else {
            // mergem in dreapta cat de mult putem
            while (st <= m && query[st] <= h[i] + p)
                ++st;
        }
    }
    if (st == m + 1)
        return true;
    return false;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> h[i];
    for (int i = 1; i <= m; ++i)
        cin >> query[i];
    sort(h + 1, h + n + 1);
    sort(query + 1, query + m + 1);
    ll rez = 0, p = 1LL << 40;
    for (; p; p >>= 1LL)
        if (solve(rez + p))
            ;
        else
            rez += p;
    rez ++;
    if (solve(0))
        rez = 0;
    cout << rez << "\n";
    return 0;
}
