#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5 + 5;

vector<int> vertex[kMaxN];
int parent[kMaxN];

int n;
vector<int> answer;

int subtree[kMaxN];

void Solve(int node) {
    subtree[node] = 1;
    for (auto itr : vertex[node]) {
        Solve(itr);
        subtree[node] += subtree[itr];
    }

    sort(vertex[node].begin(), vertex[node].end(),
         [&](int a, int b) { return subtree[a] > subtree[b]; });
}

set<int> under_el[kMaxN];

void SolveUnder(int node) {
    int under_size = 1;
    for (auto itr : vertex[node]) {
        under_size += subtree[itr];
        SolveUnder(node);
    }

    if (vertex[node].size() and n - under_size < subtree[vertex[node][0]]) {
        int mn_oth = n - under_size;
        for (auto itr : vertex[node]) {
            mn_oth = min(mn_oth, subtree[itr]);
        }
        int v = mn_oth;
        int w = subtree[vertex[node][0]];
        int oth = vertex[node][0];
        auto &s = under_el[oth];
        auto itr = s.lower_bound((w - v) / 2);
        if (itr == s.end()) {
            itr--;
        }
        int a = max(v + *itr, w - *itr);
        int b = 1e9;
        if (itr != s.begin()) {
            itr--;
            b = max(v + *itr, w - *itr);
        }

        a = min(a, b);

    } else {
        swap(under_el[node], under_el[vertex[node][0]]);
        for (int i = 1; i < (int)vertex[node].size(); i += 1) {
            int oth = vertex[node][i];
            for (auto itr : under_el[oth]) {
                under_el[node].insert(itr);
            }
        }
    }
    under_el[node].insert(subtree[node]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    answer.resize(n);
    int root = 0;
    for (int i = 1; i <= n; i += 1) {
        int p, v;
        cin >> p >> v;
        p -= 1;
        v -= 1;
        if (p == -1) {
            root = v;
        } else {
            vertex[p].push_back(v);
        }
        parent[v] = p;
    }

    Solve(root);
    for (auto itr : answer) {
        cout << itr << ' ';
    }
    cout << '\n';
    return 0;
}
