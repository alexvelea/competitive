#include <iostream>
#include <unordered_map>
#include <vector> 
#include <cmath>
using namespace std;

const int kMaxN = 305;

int a[kMaxN], b[kMaxN];
int n, nextNode;

unordered_map<int, int> valId, used;

vector<int> vertex[kMaxN];
int paired[kMaxN * kMaxN], value[kMaxN * kMaxN];

void insertEdge(int a, int v) {
    if (valId[v] == 0) {
        valId[v] = ++nextNode;
        value[nextNode] = v;
    }

    vertex[a].push_back(valId[v]);
}

bool viz[kMaxN * kMaxN];

bool findPath(int nod) {
    viz[nod] = true;
    for (auto itr : vertex[nod]) {
        if (paired[itr] == 0) {
            paired[itr] = nod;
            paired[nod] = itr;
            return true;
        }
    }

    for (auto itr : vertex[nod]) {
        if (not viz[paired[itr]] and findPath(paired[itr])) {
            paired[itr] = nod;
            paired[nod] = itr;
            return true;
        }
    }

    return false;
}

int main() {
    int n, m; cin >> n >> m;
    nextNode = n + 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        if (a[i] == 0) {
            if (1 <= b[i] and b[i] <= m) {
                insertEdge(i, b[i]);
            }
        } else {
            int mn, mx;
            if (a[i] >= 0) {
                mn = round(ceil(1.0 * (1 - b[i]) / a[i]));
                mx = round(floor(1.0 * (m - b[i]) / a[i]));
            } else {
                mn = round(ceil(1.0 * (b[i] - m) / abs(a[i])));
                mx = round(floor(1.0 * (b[i] - 1) / abs(a[i])));
            }
            mn = max(mn, 0);
            for (int itr = mn; itr <= mx and itr <= mn + n; ++itr) {
                insertEdge(i, a[i] * itr + b[i]);
            }
        }
    }

    while (1) {
        for (int i = 1; i <= n; ++i) {
            viz[i] = false;
        }
        bool ok = false;
        for (int i = 1; i <= n; ++i) {
            if (not viz[i] and paired[i] == 0) {
                ok |= findPath(i); 
            }
        }
        if (ok == false) {
            break;
        }
    }

    vector<int> rez(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        if (paired[i] != 0) {
            rez[i] = value[paired[i]];
            used[rez[i]] = 1;
        }
    }

    for (int v = 1, i = 1; i <= n; ++i) {
        if (paired[i] == 0) {
            while (used[v] == 1) {
                ++v;
            }
            used[v] = 1;
            rez[i] = v;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << rez[i] << ' ';
    }
    
    return 0;
}
