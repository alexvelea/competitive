//Problem b @ 03-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 666; // hail Satan

#define int64 long long

bool edge[kMaxN][kMaxN], solved[kMaxN];

int nodeCost[kMaxN];
int sz[kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                edge[i][j] = false;   
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            cin >> nodeCost[i];
            solved[i] = false;
            sz[i] = 0;
        }

        priority_queue<pair<int, int> > pq;

        for (int i = 1; i <= m; ++i) {
            int a, b; cin >> a >> b;
            edge[a][b] = edge[b][a] = true;
            sz[a]++;
            sz[b]++;
        }

        for (int i = 1; i <= n; ++i) {
            pq.push(make_pair(-sz[i], i));
            edge[i][i] = true;
        }

        int mx = 0;

        while (pq.size()) {
            int nod = pq.top().second;
            pq.pop();
            if (solved[nod]) {
                continue;
            }
            solved[nod] = true;
            vector<int> nearby;
            for (int i = 1; i <= n; ++i) {
                if (edge[i][nod] and not solved[i]) {
                    nearby.push_back(i);
                }
            }
//            cout << nod << '\t';
//            for (auto itr : nearby) {
//                cout << itr << '\t';
//            }
//            cout << '\n';
            for (int s = 0; s < (1 << int(nearby.size())); ++s) {
                bool ok = true;
                int cost = nodeCost[nod];
                for (int a = 0; a < int(nearby.size()); ++a) {
                    if ((1 << a) & s) {
//                        cerr << nod << '\t' << nearby[a] << '\n';
                        cost += nodeCost[nearby[a]];
                        for (int b = a + 1; b < int(nearby.size()); ++b) {
                            if ((1 << b) & s) {
//                                cout << "~" << nearby[a] << '\t' << nearby[b] << '\t' << ok << '\n';
                                if (edge[nearby[a]][nearby[b]] == false) {
                                    ok = false;
                                }
                            }
                        }
//                        cout << '\n';
                    }
                }
                if (ok) {
                    mx = max(mx, cost);
                }
            }

            for (auto itr : nearby) {
                sz[itr]--;
                pq.push(make_pair(-sz[itr], itr));
            }
        }
        cout << mx << '\n';
    }
	return 0;
}
