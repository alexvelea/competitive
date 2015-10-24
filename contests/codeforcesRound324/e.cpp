//Problem e @ 06-10-2015
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 2005;

#define int64 long long

int cost = 0;
vector<pair<int, int> > v;

int a[kMaxN], b[kMaxN], dist[kMaxN];

void Swap(int a, int b) {
    int d = b - a;
    if (d > dist[a]) {
        assert(0);
    }

    if (d > -dist[b]) {
        assert(0);
    }
    dist[a] -= d;
    dist[b] += d;
    swap(dist[a], dist[b]);
    v.push_back(make_pair(a, b));
    cost += d;
}

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i] == b[j]) {
                dist[i] = j - i;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (dist[i] < 0) {
            int poz = i;
            int last = i;
            while (poz > 0 and dist[last] < 0) {
                --poz;
                if (dist[poz] > 0) {
                    Swap(poz, last);
                    last = poz;
                }
            }
        }
    }
    cout << cost << '\n';
    cout << v.size() << '\n';
	for (auto itr : v) {
        cout << itr.first << ' ' << itr.second << '\n';
    }
    return 0;
}
