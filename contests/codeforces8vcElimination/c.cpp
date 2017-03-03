#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

const int kMaxN = 1e5+5;


vector<int> vertex[kMaxN];
int visited[kMaxN];

void Solve(int node) {
    visited[node] = true;
    for (auto itr : vertex[node]) {
        if (not visited[itr]) {
            Solve(itr);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; i += 1) {
        int x; cin >> x;
        vertex[x].push_back(i);
        vertex[i].push_back(x);
    }

    int ans = 0;
    for (int i = 1; i <= n; i += 1) {
        if (not visited[i]) {
            ans += 1;
            Solve(i);
        }
    }

    cout << ans << '\n';

    return 0;
}
