//Problem 5 @ 04-10-2015
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1700;

#define int64 long long

int n;
long double mn[kMaxN];
long double dist[kMaxN][kMaxN];
bool checked[kMaxN];
int father[kMaxN];

int x[kMaxN], y[kMaxN];
int node[30];

long double getD(int a, int b) {
    return sqrt(1.0 * (x[a] - x[b]) * (x[a] - x[b]) + 1.0 * (y[a] - y[b]) * (y[a] - y[b]));
}

void expand(int nod) {
    checked[nod] = true;
    for (int i = 1; i <= n; ++i) {
        if (mn[nod] + dist[nod][i] < mn[i]) {
            father[i] = nod;
            mn[i] = mn[nod] + dist[nod][i];
        }
    }
    return ;
}

int main() {
	ios::sync_with_stdio(false);
    if (1) {
        int m, k; cin >> n >> m >> k;
        long double v1, v2; cin >> v1 >> v2;
        v1 = max(v1, v2);
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> y[i];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = getD(i, j) / v2; 
            }
        }

        for (int i = 1; i <= m; ++i) {
            int a, b; cin >> a >> b;
            dist[a][b] = getD(a, b) / v1;
            dist[b][a] = dist[a][b];
        }

        for (int i = 1; i <= k; ++i) {
            cin >> node[i];
        }
        
        node[k + 1] = n;
        node[0] = 1;
        ++k;
        vector<int> history = {1};
        long double D = 0;
        for (int t = 1; t <= k; ++t) {
            int a = node[t - 1];
            int b = node[t];
            for (int i = 1; i <= n; ++i) {
                mn[i] = inf;
                father[i] = -1;
                checked[i] = false;
            }
            mn[a] = 0;
            father[a] = a;
            expand(a);
            while (checked[b] == false) {
                int mnV = inf, where = -1;
                for (int i = 1; i <= n; ++i) {
                    if (mn[i] < mnV and checked[i] == false) {
                        where = i;
                        mnV = mn[i];
                    }
                }
                expand(where);
            }
            D += mn[b];
            vector<int> here;
            int nod = b;
            while (nod != a) {
                here.push_back(nod);
                nod = father[nod];
            }
            reverse(here.begin(), here.end());
            for (auto itr : here) {
                history.push_back(itr);
            }
        }
        cout << fixed << setprecision(13) << D << '\n';
        for (auto itr : history) {
            cout << itr << ' ';
        }
        cout << '\n';
    }
    return 0;
}
