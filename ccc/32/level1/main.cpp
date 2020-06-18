#include <iostream>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    int mn = 1e9;
    int mx = -1e9;
    long long avg = 0;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            int x; cin >> x;
            mn = min(mn, x);
            mx = max(mx, x);
            avg += x;
        }
    }

    cout << mn << ' ' << mx << ' ' << (avg / (n * m)) << '\n';
}
