#include <iostream>
#include <map>
using namespace std;

const int kMaxN = 1e3;

int country_id[kMaxN][kMaxN];

int dx[4] = {0, 0, +1, -1};
int dy[4] = {-1, +1, 0,0}; 

int main() {
    int n, m; cin >> n >> m;
    int mn = 1e9;
    int mx = -1e9;
    long long avg = 0;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            int x; cin >> x;
            int c; cin >> c;
            country_id[i][j] = c;
        }
    }

    for (int i = 1; i <= n; i += 1) {
        country_id[i][0] = -1;
        country_id[i][m + 1] = -1;
    }

    for (int i = 1; i <= m; i += 1) {
        country_id[0][i] = -1;
        country_id[n + 1][i] = -1;
    }

    map<int, int> ans;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            bool ok = false;
            for (int d = 0; d < 4; d += 1) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                if (country_id[nx][ny] != country_id[i][j]) {
                    ok = true;
                }
            }

            if (ok) {
                ans[country_id[i][j]] += 1;
            }
        }
    }

    for (auto& itr : ans) {
        cout << itr.second << '\n';
    }
}
