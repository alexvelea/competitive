//Problem b @ 12-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

int n, m;
string row[1000];

bool update(int i, int j) {
    if (i == 0 or i == 4) {
        return false;
    }
    if (row[i][j] == '.' or row[i][j] == 's') {
        row[i][j] = 's';
        return true;
    }
    return false;
}

int main() {
	ios::sync_with_stdio(false);
	int t; cin >> t;
    while (t--) {
        int k;
        cin >> m >> k;
        n = 3;
        for (int i = 1; i <= n; ++i) {
            cin >> row[i];
            row[i] += ".....";
        }
        int c = 0;
        bool ok = false;
        while (c < m) {
            for (int i = 1; i <= n; ++i) {
                if (row[i][c] == 's') {
                    if (update(i, c + 1)) {
                        update(i - 1, c + 1);
                        update(i + 1, c + 1);
                    }
                }
            }
            ++c;
            for (int i = 1; i <= n; ++i) {
                if (row[i][c] == 's') {
                    update(i, c + 2);
                }
            }
            c += 2;
        }
        for (int j = m; j - 5 < m; ++j) {
            for (int i = 1; i <= n; ++i) {
                if (row[i][j] == 's') {
                    ok = true;
                }
            }
        }
        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
