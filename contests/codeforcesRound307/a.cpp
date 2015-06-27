//Problem a @ 16-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 2005;
const double eps = 1e-7;

#define int64 long long

vector<pair<int, int> > ev;
int rez[kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        ev.push_back(make_pair(-x, i));
    }
    sort(ev.begin(), ev.end());
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n and ev[i].first == ev[j].first) {
            rez[ev[j].second] = i + 1;
            ++j;
        }
        i = j;
    }
    for (int i = 1; i <= n; ++i) {
        cout << rez[i] << ' ';
    }
	return 0;
}
