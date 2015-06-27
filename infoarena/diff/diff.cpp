//Problem diff @ 19-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 2e5+5;

#define int64 long long

ifstream fin("diff.in");
ofstream fout("diff.out");

pair<int, int> rez[kMaxN];
int target[kMaxN];
int el[kMaxN];

int where[2 * kMaxN];
#define where (where + kMaxN)

void solve(int n, int q) {
    int mxVal = 0, mxWhere = -1, minUntil = 0;
    for (int i = 1; i <= n; ++i) {
        if (el[i] - minUntil > mxVal) {
            mxVal = el[i] - minUntil;
            mxWhere = i;
        }
        if (el[i] < minUntil) {
            minUntil = el[i];
        }
    }
    
    for (int i = 0; i < mxWhere; ++i) {
        where[el[i]] = i + 1;
    }

    for (int i = 1; i <= q; ++i) {
        if (abs(target[i]) <= n and where[el[mxWhere] - target[i]] != 0) {
            rez[i] = make_pair(where[el[mxWhere] - target[i]], mxWhere);
        }
    }

    for (int i = 0; i < mxWhere; ++i) {
        where[el[i]] = 0;
    }
}

int main() {
    int n, q; fin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        fin >> el[i];
        if (el[i] == 0) {
            el[i] = -1;
        }
        el[i] += el[i - 1];
    }

    for (int i = 1; i <= q; ++i) {
        rez[i] = make_pair(-1, -1);;
        fin >> target[i];
    }

	solve(n, q);
    for (int i = 1; i <= n; ++i) {
        el[i] = -el[i];
    }
    
    for (int i = 1; i <= q; ++i) {
        target[i] = -target[i];
    }
    solve(n, q);


    for (int i = 1; i <= q; ++i) {
        if (rez[i].first == -1) {
            fout << "-1\n";
        } else {
            fout << rez[i].first << ' ' << rez[i].second << '\n';
        }
    }
    return 0;
}
