//Problem c @ 22-08-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

int n, m;

void write() {
    cout << "YES\n";
    for (int i = 1; i <= m; ++i) {
        cout << val[i];
    }
    exit(0);
}

void checkNode(int nod, queue<int> &q) {
    for (auto itr : edge[nod]) {
        if (not isSet[abs(itr)]) {
            if (itr > 0) {
                
            }
        }
    }
}

void solve(bool initVal) {
    for (int i = 1; i <= m; ++i) {
        isSet[i] = false;
        val[i] = 0;
    }
    
    for (int i = 1; i <= n; ++i) {
        isSolve[i] = false;
    }
    
    queue<int> Q;

    for (int i = 1; i <= m; ++i) {
        if (where[i].first == where[i].second) {
            isSolved[where[i].first] = true;
            isSet[i] = true;
            checkNode(i, Q);
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int nr; cin >> nr;
        while (nr--) {
            int x; cin >> x;
            if (x < 0) {
                where[-x].second = i;
            } else {
                where[x].first = i;
            }

            edge[i].push_back(x);
        }
    }

    solve(false);
    solve(true);
    cout << "NO\n";
    return 0;
}
