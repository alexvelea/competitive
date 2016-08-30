#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, kMaxN = 1e5+5;

vector<int> edge[2][kMaxN];

int best[kMaxN];

int main() {
    int n, m, q; cin >> n >> m >> q;
    for (int i = 1; i <= m; i += 1) {
        int a, b; cin >> a >> b;
        edge[0][a].push_back(b);
        edge[1][b].push_back(a);
    }

    for (int i = 1; i <= n; i += 1) {
        best[i] = +inf;
    }

    best[1] = 0;
    queue<pair<int, int>> bfs;
    bfs.push({1, 0});

    while (bfs.size()) {
        int nod = bfs.front().first;
        int cost = bfs.front().second;

        bfs.pop();
        if (cost == best[nod]) {
            bfs.push({nod, cost + 1});
        }

        for (auto itr : edge[cost % 2][nod]) {
            if (best[itr] > cost + 1) {
                best[itr] = cost + 1;
                bfs.push({itr, cost + 1});
            }
        }
    }

    while (q--) {
        int x; cin >> x;
        if (best[n] > x) {
            cout << "FML\n";
        } else {
            cout << "GGMU\n";
        }
    }
    return 0;
}
