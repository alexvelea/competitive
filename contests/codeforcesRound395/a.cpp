#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

vector<int> vertex[kMaxN];

int color[kMaxN];
int uppertree_color[kMaxN];
int subtree_color[kMaxN];
bool visited[kMaxN];
int father[kMaxN];

void df(int node) {
    subtree_color[node] = color[node];
    visited[node] = true;
    for (auto itr : vertex[node]) {
        if (visited[itr]) {
            continue;
        }
        df(itr);
        father[itr] = node;
        if (subtree_color[itr] != color[node]) {
            subtree_color[node] = -1;
        }
    }
    
    
    visited[node] = false;
}

void df2(int node) {
    visited[node] = true;
    int my_color = 0;
    int subtree_nodes = 0;
    bool bad = false;
    int nr_bad = 0;
    for (auto itr : vertex[node]) {
        if (visited[itr]) {
            if (uppertree_color[itr] != color[node] and uppertree_color[itr] != 0) {
                bad = true;
            }
        } else {
            if (color[node] == subtree_color[itr]) {
                my_color += 1;
            }

            if (subtree_color[itr] == -1) {
                nr_bad += 1;
            }

            subtree_nodes += 1;
        }
    }

    if (my_color + 1 < subtree_nodes) {
        bad = true;
    }

    if (uppertree_color[node] != color[node] and node != 1) {
        bad = true;
    }

    if (nr_bad > 1) {
        bad = true;
    }

    if (bad) {
        for (auto itr : vertex[node]) {
            if (not visited[itr]) {
                uppertree_color[itr] = -1;
                df2(itr);
            }
        }
    } else {
        for (auto itr : vertex[node]) {
            if (not visited[itr]) {
                if (subtree_color[itr] != color[node] || my_color == subtree_nodes) {
                    uppertree_color[itr] = color[node];
                } else {
                    uppertree_color[itr] = -1;
                }

                df2(itr);
            }
        }
    }
    
    visited[node] = false;
    return;
}

void df3(int node) {
    visited[node] = true;
    bool ok = true;
    for (auto itr : vertex[node]) {
        if (not visited[itr]) {
            ok &= subtree_color[itr] != -1;
        }
    }

    ok &= uppertree_color[node] != -1;
    if (ok) {
        cout << "YES\n" << node << '\n';
        exit(0);
    }
    
    for (auto itr : vertex[node]) {
        if (not visited[itr]) {
            df3(itr);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i + 1 < n; i += 1) {
        int a, b; cin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    for (int i = 1; i <= n; i += 1) {
        cin >> color[i];
    }

    df(1);
    df2(1);
    df3(1);
    
    cout << "NO\n";
    return 0;
}
