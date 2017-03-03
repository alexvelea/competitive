#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int x[105][105];

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> x[i][j];
        }
    }

    int mx = 0;
    for (int i = 0; i < n; i += 1) {
        int mn = 1e9+5;
        for (int j = 0; j < m; j += 1) {
            mn = min(mn, x[i][j]);
        }

        mx = max(mx, mn);
    }

    cout << mx << '\n';
}

