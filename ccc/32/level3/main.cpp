#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int64;

const int kMaxN = 1e3 + 5;

int country_id[kMaxN][kMaxN];
bool on_border[kMaxN][kMaxN];
vector<pair<int, int>> cells[int(1e6)];

int dx[4] = {0, 0, +1, -1};
int dy[4] = {-1, +1, 0,0}; 

int main() {
    int n, m; cin >> n >> m;
    int num_countries = 0;
    for (int j = 1; j <= m; j += 1) {
        for (int i = 1; i <= n; i += 1) {
            int x; cin >> x;
            int c; cin >> c;
            country_id[i][j] = c;
            num_countries = max(num_countries, c);
            cells[c].push_back({i, j});
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
                on_border[i][j] = true;
            }
        }
    }

    for (int i = 0; i <= num_countries; i += 1) {
        auto& cells = ::cells[i];
        int64 x = 0, y = 0;
        for (auto cell : cells) {
            x += cell.first;
            y += cell.second;
        }

        x /= cells.size();
        y /= cells.size();

        vector<pair<int, pair<int, int>>> p_cells;
        for (auto cell : cells) {
            if (on_border[cell.first][cell.second]) {
                continue;
            }

            p_cells.push_back({
                    (x - cell.first) * (x - cell.first) + 
                    (y - cell.second) * (y - cell.second), {
                    cell.second, cell.first} });
        }

        sort(p_cells.begin(), p_cells.end());
        cout << p_cells[0].second.second - 1 << ' ' << p_cells[0].second.first - 1 << '\n';
    }
}
