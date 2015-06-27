//Problem d @ 27-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 2e5 + 5;

#define int64 long long

int where[kMaxN], here[kMaxN];
int el[kMaxN];
int n, q;

int solve(int last, int now, int l, int dir) {
    // 0 .. n
//    cerr << last << '\t' << now << '\t' << l << '\t'<< dir << '\n';
    if (el[now] - l > el[now - 1] and el[now] + l < el[now + 1]) {
        return now;
    }
    if (dir == +1) {
        if (now == n - 1) {
            return solve(last, now, l, -1);
        }

        int x = lower_bound(el, el + n + 1, el[now] + l + 1) - el;
        --x;

//        cerr << "!!!!!\t" << el[now] + l << "--->" << x << '\t' << el[x] << '\n'; 
        
        if (x == now and last != -1) {
            return x;
        }
        if (el[x] > el[now] + l) {
            return solve(now, now, l, -1);
        }
        
        if (x == last) {
            l = l % ((el[x] - el[now]) * 2);
            return solve(-1, now, l, +1);
        } 
        return solve(now, x, l - (el[x] - el[now]), - 1);
    } else {
        if (now == 1) {
            return solve(last, now, l, -1);
        }

        int x = lower_bound(el, el + n + 1, el[now] - l) - el;
//        cerr << "????\t" << el[now] - l << "--->" << x << '\t' << el[x] << '\n'; 
        if (x == now and last != -1) {
            return x;
        }
        if (el[x] < el[now] - l) {
            return solve(now, now, l, +1);
        }

        if (x == last) {
            l = l % ((el[now] - el[x]) * 2);
            return solve(-1, now, l, -1);
        }
        return solve(now, x, l - (el[now] - el[x]), +1);
    }
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n >> q;
    vector<pair<int, int> > ev;
    for (int i = 1; i <= n; ++i) {
        cin >> el[i];
        ev.push_back(make_pair(el[i], i));
    }
    sort(ev.begin(), ev.end());
    el[0] = 2 * -inf;
    el[n + 1] = 2 * inf;
    for (int i = 1; i <= n; ++i) {
        here[i] = ev[i - 1].second;
        where[ev[i - 1].second] = i;
        el[i] = ev[i - 1].first;
    }
    ++n;
//    for (int i = 0; i <= n; ++i) {
//        cerr << i << '\t' << el[i] << "!!\n";
//    }

	while (q--) {
        int poz, l; cin >> poz >> l;
        poz = where[poz];
         if (n == 1) {
            cout << 1 << '\n';
        } else {
           cout << here[solve(-1, poz, l, +1)] << '\n';
        }
    }
    return 0;
}
