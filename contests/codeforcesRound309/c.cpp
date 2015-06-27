//Problem c @ 25-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1e5 + 5, kMod = 1000000007;

#define int64 long long

bool viz[kMaxN], color[kMaxN];
vector<pair<int, int> > vertex[kMaxN];

bool ok = true;

void df(int nod) {
    viz[nod] = true;
    for (auto itr : vertex[nod]) {
        int oth = itr.first;
        if (not viz[oth]) {
            color[oth] = color[nod] ^ itr.second;
            df(oth);
        } else {
            if (color[oth] != (color[nod] ^ itr.second)) {
                ok = false;
            }
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        c ^= 1;
        vertex[a].push_back(make_pair(b, c));
        vertex[b].push_back(make_pair(a, c));
    }
    
    for (int i = 1; i <= n; ++i) {
        color[i] = -1;
    }

    for (int i = 1; i <= n; ++i) {
        if (viz[i] == 0) {
            color[i] = 0;
            df(i);
        }
    }

    if (ok == false) {
        cout << "0\n";
        return 0;
    }

    int nrC = -1;
    for (int i = 1; i <= n; ++i) {
        viz[i] = false;
    }
    for (int i = 1; i <= n; ++i) {
        if (not viz[i]) {
            df(i);
            ++nrC;
        }
    }
    int rez = 1;
    while (nrC) {
        rez *= 2;
        rez %= kMod;
        --nrC;
    }
    cout << rez << '\n';
    return 0;
}
