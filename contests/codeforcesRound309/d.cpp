//Problem d @ 25-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1e5 + 5;

#define int64 long long

int n, m, k; 
bool bad[kMaxN];
vector<int> vertex[kMaxN];

void solve() {
    priority_queue<pair<double, int> > pq;
    vector<int> events(n + 1, 0);
    vector<bool> good(n + 1, false), viz(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (not bad[i] and vertex[i].size()) {
            good[i] = true;
        }
    }

    vector<int> nrGood(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (auto itr : vertex[i]) {
            if (bad[itr] == false) {
                ++nrGood[i];
            }
        }
        if (good[i]) {
            pq.push(make_pair(-1.0 * nrGood[i] / vertex[i].size(), i));
        }
    }

    int steps = 0, when = 0;
    double mx = -1.0;

    while (pq.size()) {
        int nod = pq.top().second;
        double exp = -pq.top().first;
        pq.pop();

        if (viz[nod]) {
            continue;
        }
        if (mx < exp) {
            mx = exp;
            when = steps;
        }

        events[steps] = nod;
        viz[nod] = true;
        ++steps;
        good[nod] = false;
       
        for (auto itr : vertex[nod]) {
            if (good[itr] == true) {
                nrGood[itr]--;
                pq.push(make_pair(-1.0 * nrGood[itr] / vertex[itr].size(), itr));
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (not bad[i] and vertex[i].size()) {
            good[i] = true;
        }
    }
    for (int i = 0; i < when; ++i) {
        good[events[i]] = false;
    }
    int _n = 0;
    for (int i = 1; i <= n; ++i) {
        if (good[i] == true) {
            ++_n;
        }
    }
    cout << _n << '\n';
    for (int i =1 ; i <= n; ++i) {
        if (good[i]) {
            cout << i << ' ';
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    

    for (int i = 1; i <= k; ++i) {
        int x; cin >> x;
        bad[x] = true;
    }

    for (int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }
    solve();
	return 0;
}
