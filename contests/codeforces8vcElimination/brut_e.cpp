#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

int edge[10][10];
int n;

int Bf(int node, int color) {
    vector<int> best(n + 1, +inf);
    vector<int> viz(n + 1, 0);
    best[node] = 0;

    int ans = 0;
    for (int i = 1; i <= n; i += 1) {
        int mn = +inf;
        int who = 0;
        for (int j = 1; j <= n; j += 1) {
            if (viz[j]) {
                continue;
            }

            if (mn > best[j]) {
                mn = best[j];
                who = j;
            }
        }

        if (who == 0) {
            return 0;
        }

        viz[who] = true;
        ans = mn;

        for (int i = 1; i <= n; i += 1) {
            if (edge[i][who] != color) {
                continue;
            }

            if (best[i] > best[who] + 1) {
                best[i] = best[who] + 1;
            }
        }
    }

    return ans;
}

int Solve() {
    int mn = +inf;
    for (int c = 0; c < 2; c += 1) {
        int mx = 0;
        for (int i = 1; i <= n; i += 1) {
            mx = max(mx, Bf(i, c));
        }
        mn = min(mn, mx);
    }


    if (mn == 2) {
        for (int i = 1; i <= n; i += 1) {
            for (int j = i + 1; j <= n; j += 1) {
                if (edge[i][j] == 1) {
                    cout << i << ' ' << j << '\n';
                }
            }
        }
        exit(0);
    }
    return mn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    int m = n * (n - 1) / 2;
    cerr << m << '\n';
    
    vector<int> viz(n + 1, 0);

    for (int st = 0; st < (1 << m); st += 1) {
        int edge_id = 0;
        for (int i = 1; i <= n; i += 1) {
            for (int j = i + 1; j <= n; j += 1) {
                int c = st & (1 << edge_id);
                c = (c != 0);
                edge_id += 1;
                edge[i][j] = c;
                edge[j][i] = c;
            }
        }

        int x = Solve();
        viz[x] = true;
    }   

    for (auto itr : viz) {
        cout << itr << '\t';
    }

    return 0;
}
