//Problem 3 @ 04-10-2015
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int kMaxN = 1e5 + 5, inf = 2e9;

#define int64 long long

bool ok = true;

struct Limit {
    int val[2];
    Limit() {
        val[0] = -inf;
        val[1] = +inf;
    }
    Limit(int _a, int _b) {
        val[0] = _a;
        val[1] = _b;
    }
    Limit merge(Limit a) {
        Limit b = *this;
        Limit rez;
        rez.val[0] = max(a.val[0], b.val[0]);
        rez.val[1] = min(a.val[1], b.val[1]);
        if (rez.val[0] > rez.val[1]) {
            ok = false;
        }
        return rez;
    }
} elLimit[kMaxN];

vector<pair<int, bool> > vertex[kMaxN], reverseV[kMaxN];

bool viz[kMaxN];
int father[kMaxN];

stack<int> stk;
void df1(int nod) {
    viz[nod] = true;
    for (auto itr : vertex[nod]) {
        if (not viz[itr.first]) {
            df1(itr.first);
        }
    }
    stk.push(nod);
}

void df2(int nod, int p) {
    viz[nod] = true;
    father[nod] = p;
    for (auto itr : reverseV[nod]) {
        if (not viz[itr.first]) {
            df2(itr.first, p);
        }
    }
}

int rez[kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int m, n; cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        int type, t1, v1, t2, v2;
        cin >> type >> t1 >> v1 >> t2 >> v2;
        if (t1 or t2) {
            if (t1) {
                v1 += type;
            } else if (t2) {
                v2 -= type;
            }
            Limit aux;
            if (t1) {
                aux = aux.merge(Limit(v1, +inf)); 
            }
            if (t2) {
                aux = aux.merge(Limit(-inf, v2));
            }

            if (not t1) {
                elLimit[v1] = elLimit[v1].merge(aux);
            }
            if (not t2) {
                elLimit[v2] = elLimit[v2].merge(aux);
            }
        } else {
            // intre elemente
            vertex[v2].push_back({v1, type});
            reverseV[v1].push_back({v2, type});
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (not viz[i]) {
            df1(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        viz[i] = false;
        father[i] = i;
    }

    while (stk.size()) {
        int nod = stk.top();
        stk.pop();
        if (not viz[nod]) {
            df2(nod, nod);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (father[i] != i) {
            elLimit[father[i]] = elLimit[father[i]].merge(elLimit[i]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        vector<pair<int, bool> > aux;
        aux = vertex[i];
        vertex[i].clear();
        for (auto itr : aux) {
            vertex[father[i]].push_back({father[itr.first], itr.second});
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (auto itr : vertex[i]) {
            if (itr.first == i and itr.second == 1) {
                ok = false;
            }
        }
    }

	if (not ok) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        viz[i] = false;
    }
    for (int i = 1; i <= n; ++i) {
        if (not viz[i] and father[i] == i) {
            df1(i); 
        }
    }

    vector<int> STK;
    while (stk.size()) {
        int nod = stk.top();
        stk.pop();
        STK.push_back(nod);
    }

    reverse(STK.begin(), STK.end());

    for (auto nod : STK) {
//        cerr << nod << "~\n";
        int mx = -inf;
        for (auto itr : vertex[nod]) {
            int v = rez[itr.first] + itr.second;
            mx = max(mx, v);
        }
        Limit aux(mx, +inf);
        elLimit[nod] = elLimit[nod].merge(aux);
        rez[nod] = elLimit[nod].val[0];
    }

    if (not ok) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        if (father[i] != i) {
            rez[i] = rez[father[i]];
        }
        cout << rez[i] << '\n';
    }
    return 0;
}
