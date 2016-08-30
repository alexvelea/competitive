#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, kMaxN = 1e5+5;

vector<int> edge[kMaxN];

vector<int> result[2];
bool visited[kMaxN];
int depth[kMaxN];

void df(int nod) {
    visited[nod] = true;
    result[depth[nod]].push_back(nod);
    for (auto itr : edge[nod]) {
        if (not visited[itr]) {
            depth[itr] = 1 ^ depth[nod];
            df(itr);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m; cin >> n >> m;       
    for (int i = 1; i <= m; i += 1) {
        int x, y; cin >> x >> y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    for (int i = 1; i <= n; i += 1) {
    if (not visited[i]) { df(i); }}   

    bool ok = true;
    for (int i = 1; i <= n; i += 1) {
        for (auto itr : edge[i]) {
            if (depth[i] == depth[itr]) {
                ok = false;
            }
        }
    }

    if (not ok) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 0; i < 2; i +=1 ) {
    cout << result[i].size() << '\n';
    for (auto itr : result[i]) {
        cout << itr << ' ';
    }
    cout << '\n';
}
    return 0;
}
