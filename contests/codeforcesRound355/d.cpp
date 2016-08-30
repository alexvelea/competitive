#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

typedef long long int64;

const int kMaxN = 305, kMaxP = 305 * 305, inf = 0x3f3f3f3f;

int element[kMaxN][kMaxN];
int best[kMaxN][kMaxN];
int n, m, p; 
vector<pair<int, int>> coords[kMaxP];

int dist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void Brut(int color) {
    for (auto a : coords[color - 1]) {
        int cost = best[a.first][a.second];
        if (color == 1) {
            cost = 0;
        }

        for (auto b : coords[color]) {
            best[b.first][b.second] = min(best[b.first][b.second], cost + dist(a, b));
        }
    }
}

void Djk(int color) {
    vector<vector<int>> best_cost(n + 2, vector<int>(m + 2, inf));
    priority_queue<pair<int, pair<int, int>>> pq;
    for (auto itr : coords[color - 1]) {
        best_cost[itr.first][itr.second] = best[itr.first][itr.second];
        pq.push({-best[itr.first][itr.second], itr});
    }

    const int dx[] = {+1, -1, 0, 0};
    const int dy[] = {0, 0, +1, -1};

    while (pq.size()) {
        int cost;
        pair<int, int> pos;
        cost = -pq.top().first;
        pos = pq.top().second;
        pq.pop();
        if (best_cost[pos.first][pos.second] != cost) {
            continue;
        }

        for (int d = 0; d < 4; d += 1) {
            int nx = pos.first + dx[d];
            int ny = pos.second + dy[d];
            if (nx == 0 or nx == n + 1 or ny == 0 or ny == m + 1) {
                continue;
            }

            if (best_cost[nx][ny] > cost + 1) {
                best_cost[nx][ny] = cost + 1;
                pq.push({-cost - 1, {nx, ny}});
            }
        }
    }

    for (auto itr : coords[color]) {
        best[itr.first][itr.second] = best_cost[itr.first][itr.second];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            best[i][j] = +inf;
            cin >> element[i][j];
            coords[element[i][j]].push_back({i, j});
        }
    }

    coords[0].push_back({1, 1});
    for (int color = 1; color <= p; color += 1) {
        if (coords[color - 1].size() * coords[color].size() < n * m * (rand() % 10 + 10)) {
            Brut(color);
        } else {
            Djk(color);
        }
    }
   
    int mn = inf;
    for (auto position : coords[p]) {
        mn = min(mn,  best[position.first][position.second]);
    }
    cout << mn << '\n';
    return 0;
}
