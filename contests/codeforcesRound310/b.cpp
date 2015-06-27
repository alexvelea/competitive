//Problem b @ 27-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 2e5 + 5;
const double eps = 1e-7;

#define int64 long long

int64 bridge[kMaxN];
int64 x[kMaxN], y[kMaxN];

int rez[kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<pair<int64, int> > ev; 
    vector<tuple<int64, int64, int> > ev2;
    priority_queue<pair<int64, int> > pq;

    for (int i = 1; i < n; ++i) {
        int64 a = x[i + 1] - y[i];
        int64 b = y[i + 1] - x[i];
        if (b <= 0) {
            cout << "No";
            return 0;
        }
        a = max(a, 1LL);
        ev2.push_back(make_tuple(a, b, i));
    }

    for (int i = 1; i <= m; ++i) {
        cin >> bridge[i];
        ev.push_back(make_pair(bridge[i], i));
    }
    sort(ev.begin(), ev.end());
    sort(ev2.begin(), ev2.end());
    for (int i = 1; i < n; ++i) {
        rez[i] = -1;
    }

    int itrEv2 = 0;

    for (auto itrEv : ev) {
        int64 s = itrEv.first;
        while (itrEv2 < int(ev2.size())) {
            int64 a, b;
            int ind;
            tie(a, b, ind) = ev2[itrEv2];
            if (a <= s) {
                pq.push(make_pair(-b, ind));
                ++itrEv2;
            } else {
                break;
            }
        }

        if (pq.size()) {
            if (-pq.top().first < s) {
                cout << "No\n";
                return 0;
            }
            rez[pq.top().second] = itrEv.second;
            pq.pop();
        }
    }
    if (itrEv2 != int(ev2.size())) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    for (int i = 1; i < n; ++i) {
        cout << rez[i] << ' ';
    }
	return 0;
}
