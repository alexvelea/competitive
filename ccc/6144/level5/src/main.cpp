#include "debug.hpp"

using namespace std;

int dx[6] = {-1, -1, 0, +1, +1, 0};
int dy[6] = {-1, +1, +2, +1, -1, -2};


int n, m, x, y;
vector<string> s;

bool check() {
    int n = s.size();
    int m = s[0].size();

    bool escaped = false;
    vector<vector<bool>> visited(n, vector<bool>(m));
    vector<pair<int, int>> q;
    q.push_back({x, y});
    visited[x][y] = true;
    while (q.size()) {
        auto p = q.back();
        q.pop_back();

        for (int d = 0; d < 6; d += 1) {
            int nx = p.first + dx[d];
            int ny = p.second + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (s[nx][ny] == 'O' && visited[nx][ny] == false) {
                    visited[nx][ny] = true;
                    q.push_back({nx, ny});
                }
            } else {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int t; cin >> t;
    cout << t << '\n';
    cout << '\n';
    string S;
    getline(cin, S);
    getline(cin, S);

    while (t--) {
        s.clear();
        int additional; cin >> additional;
        getline(cin, S);

        while (1) {
            getline(cin, S);
            if (S == "\n" || S == "" || S == "\r") {
                break;
            }
            s.push_back(S.substr(0, S.size()-1));
        }

        n = s.size();
        m = s[0].size();

        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < m; j += 1) {
                if (s[i][j] == 'W') {
                    x = i;
                    y = j;
                }
            }
        }

        bool escaped = true;
        while (1) {
            int i = rand() % (1 << 6);
            int used = 0;
            bool bad = false;
            for (int d = 0; d < 6; d += 1) {
                if ((1 << d) & i) {
                    used++;
                } else {
                    continue;
                }

                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (s[nx][ny] == 'O') {
                    } else {
                        bad = true;
                    }
                } else {
                    bad = true;
                }
            }

            if (bad || used > additional) {
                continue;
            }

            vector<pair<int, int>> positions;
            for (int d = 0; d < 6; d += 1) {
                if ((1 << d) & i) {
                } else {
                    continue;
                }
                int nx = x + dx[d];
                int ny = y + dy[d];
                s[nx][ny] = 'X';
                positions.push_back({nx, ny});
            }

            int remaining = additional - used;

            for (int i = 0; i < remaining; i += 1) {
                while (1) {
                    int x = rand() % n;
                    int y = rand() % m;
                    if (s[x][y] == 'O') {
                        positions.push_back({x, y});
                        s[x][y] = 'X';
                        break;
                    }
                }
            }

            if (check() == false) {
                escaped = false;
                break;
            }

            for (auto itr : positions) {
                s[itr.first][itr.second] = 'O';
            }
        }

        for (auto itr : s) {
            cout << itr << '\n';
        }
        if (t > 0) {
            cout << '\n';
        }
    }
}