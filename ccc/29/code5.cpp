#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int kMaxN = 3005;
int height[kMaxN][kMaxN];
int visited[kMaxN][kMaxN];
int building[kMaxN][kMaxN];
bool can_hotspot[kMaxN][kMaxN];
bool can_zone[kMaxN][kMaxN];

vector<pair<int, int>> sols;

int dx[4] = {+1, -1, +0, +0};
int dy[4] = {+0, +0, +1, -1};

int n, m, s;

int step = 0;
int x_sum, y_sum, cnt;

int mx_x, mx_y, mn_x, mn_y;

void Fill(int x, int y, int h) {
    if (visited[x][y] or height[x][y] != h) {
        return;
    }

    visited[x][y] = step;
    cnt += 1;
    x_sum += x;
    y_sum += y;

    mx_x = max(mx_x, x);
    mx_y = max(mx_y, y);
    mn_x = min(mn_x, x);
    mn_y = min(mn_y, y);

    for (int d = 0; d < 4; d += 1) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (0 <= nx  and nx < n and 0 <= ny and ny < m) {
            Fill(nx, ny, h);
        }
    }
    
}

void Solve(int x, int y) {
    step += 1;
    x_sum = 0;
    y_sum = 0;
    cnt = 0;

    mx_x = 0;
    mx_y = 0;
    mn_x = 1e9;
    mn_y = 1e9;

    Fill(x, y, height[x][y]);
/*
    cerr << 1.0 * x_sum / cnt << '\t' << 1.0 * y_sum / cnt << '\t' << cnt << '\n';
    int c_x = 1.0 * x_sum / cnt;
    int c_y = 1.0 * y_sum / cnt;
*/

    int c_x = mn_x + (mx_x - mn_x) / 2.0;
    int c_y = mn_y + (mx_y - mn_y) / 2.0;
    if (building[c_x][c_y] == building[x][y]) {
        sols.push_back({c_x, c_y});
    } else {
        cerr << "~~~~~~~~~~~~\n";
    }
}

int main() {
    cin >> n >> m;
    cin >> s;

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> height[i][j];
/*            
            if (height[i][j]) {
                cout << "#";
            } else {
                cout << " ";
            }
*/            
        }
//        cout << '\n';
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (height[i][j] == 0 or visited[i][j]) {
                continue;
            }

            step += 1;
            Fill(i, j, height[i][j]);
        }
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            building[i][j] = visited[i][j];
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i <= n - s; i += 1) {
        for (int j = 0; j <= m - s; j += 1) {
            if (height[i][j] == 0) {
                continue;
            }

            bool ok = true;
            for (int k = 0; k < s; k += 1) {
                for (int l = 0; l < s; l += 1) {
                    ok &= (height[i][j] == height[i + k][j + l]);
                }
            }

            if (ok) {
                can_hotspot[i][j] = true;
            }
        }
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (!can_hotspot[i][j]) {
                continue;
            }
            for (int k = 0; k < s; k += 1) {
                for (int l = 0; l < s; l += 1) {
                    can_zone[i + k][j + l] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (!can_zone[i][j]) {
                height[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (height[i][j] == 0 or visited[i][j]) {
                continue;
            }
            Solve(i, j);
       }
    }

/*

        }
    }
*/
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (visited[i][j]) {
                cerr << char('0' + visited[i][j]);
            } else {
                cerr << ' ';
            }
        }
        cerr << '\n';
    }


    sort(sols.begin(), sols.end());
    for (int i = 0; i < (int)sols.size(); i += 1) {
        cout << i << ' ' << sols[i].first << ' ' << sols[i].second << ' ';
    }
    cout << '\n';
}

