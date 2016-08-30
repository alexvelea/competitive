#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1e5+5;

bool visited[kMaxN];
int inside[kMaxN];
vector<int> vertex[kMaxN];

int max_match[kMaxN];

int label[kMaxN], friend_label[kMaxN];

vector<int> topo;

void df(int nod) {
    visited[nod] = true;
    topo.push_back(nod);
    for (auto itr : vertex[nod]) {
        inside[itr] -= 1;
        if (inside[itr] == 0) {
            df(itr);
        }
    }
    return;
}

int main() {
    ifstream cin("marvel.in");
    ofstream cout("marvel.out");

    int n, m, k, p; cin >> n >> m >> k >> p;
    for (int i = 1; i <= n; i += 1) {
        cin >> label[i];
    }

    for (int i = 0; i < p; i += 1) {
        cin >> friend_label[i];
    }

    for (int i = 1; i <= m; i += 1) {
        int a, b; cin >> a >> b;
        vertex[b].push_back(a);
        inside[a] += 1;
    }

    for (int i = 1; i <= n; i += 1) {
        if (not visited[i] and inside[i] == 0) {
            df(i);
        }
    }

    reverse(topo.begin(), topo.end());

    for (auto itr : topo) {
        int mx = 0;
        for (auto oth : vertex[itr]) {
            mx = max(mx, max_match[oth]);
        }

        if (mx != p and label[itr] == friend_label[mx]) {
            mx += 1;
        }

        max_match[itr] = mx;
    }

    vector<int> res;
    for (int i = 1; i <= n; i += 1) {
        if (max_match[i] == p) {
            res.push_back(i);
        }
    }

    cout << res.size() << '\n';
    for (auto itr : res) {
        cout << itr << ' ';
    }

    return 0;
}
