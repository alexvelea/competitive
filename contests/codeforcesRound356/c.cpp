#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int kMaxN = 505;

char el[kMaxN][kMaxN];
int label[kMaxN][kMaxN];
vector<pair<int, int>> who[kMaxN * kMaxN];
int num_label = 0;

int partial_sums[kMaxN][kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            cin >> el[i][j];
        }
    }
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            if (el[i][j] == '.' and label[i][j] == 0) {
                label[i][j] = ++num_label;
                vector<pair<int, int>> bfs({{i, j}});
                who[num_label].push_back({i, j});
                while (bfs.size()) {
                    pair<int, int> coord = bfs.back();
                    bfs.pop_back();
                    const int dx[4] = {1, -1, 0, 0};
                    const int dy[4] = {0, 0, 1, -1};
                    for (int d = 0; d < 4; d += 1) {
                        int nx = coord.first + dx[d];
                        int ny = coord.second + dy[d];
                        if (el[nx][ny] == '.' and label[nx][ny] == 0) {
                            bfs.push_back({nx, ny});
                            label[nx][ny] = num_label;
                            who[num_label].push_back({nx, ny});
                        }
                    }
                }
            }
        }
    }

    vector<pair<int
    for (int label = 1; label <= num_label; label += 1) {
        sort(who[label].begin(), who[label].end());
        unordered_map<int, bool> touched_cols;

    }

    return 0;
}
