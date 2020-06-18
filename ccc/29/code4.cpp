#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int kMaxN = 3005;
int height[kMaxN][kMaxN];

int main() {
    int n, m; cin >> n >> m;
    int s; cin >> s;
    map<int, int> viz;
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> height[i][j];
        }
    }

    vector<pair<int, int>> sols;

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (height[i][j] == 0) {
                continue;
            }

            int x = 0;
            int y = 0;
            int h = height[i][j];

            while (height[i + x][j] == h) {
                x += 1;
            }

            while (height[i][j + y] == h) {
                y += 1;
            }

            x -= 1;
            y -= 1;

            for (int l = 0; l <= x; l += 1) {
                for (int k = 0; k <= y; k += 1) {
                    height[i + l][j + k] = 0;
                }
            }

            if (x >= 3 and y >= 3) {
                sols.push_back({
                    (x) / 2.0 + i,
                    (y) / 2.0 + j,
                });
            }
        }
    }

    sort(sols.begin(), sols.end());
    for (int i = 0; i < (int)sols.size(); i += 1) {
        cout << i << ' ' << sols[i].first << ' ' << sols[i].second << ' ';
    }
    cout << '\n';
}

