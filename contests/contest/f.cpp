//Problem f @ 08-08-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    
    vector<pair<int, int> > event, father(n + 1);
    map<pair<int, int>, vector<int> > howMany;
    vector<int> dp(n + 1, 0), fatherInd(n + 1, 0);


    for (int i = 1; i <= n; ++i) {
        int a, b; cin >> a >> b;
        if (a + b > n) {
            continue;
        }
        howMany[make_pair(a, b)].push_back(i);
        event.push_back(make_pair(a, b));
    }

    sort(event.begin(), event.end());
    int mx = 0, mxInd = 0;

    int ind = 1;
//    for (pair<int, int> itr : event) {
    for (int i = 0; i < int(event.size()); ++i) {
        pair<int, int> itr = event[i];

        while (ind <= itr.first) {
            if (mx < dp[ind]) {
                mx = dp[ind];
                mxInd = ind;
            }
            ++ind;
        }
        
        int remaining = n - itr.second;
        int inside = min(n - itr.first - itr.second, int(howMany[itr].size()));
        if (dp[remaining] < mx + inside) {
            dp[remaining] = mx + inside;
            father[remaining] = itr;
            fatherInd[remaining] = mxInd;
        }
    }

    while (ind <= n) {
        if (mx < dp[ind]) {
            mx = dp[ind];
            mxInd = ind;
        }
        ++ind;
    }
//    cerr << mxInd << '\t' << mx << '\n';
    vector<bool> good(n + 1);
    while (mxInd != 0) {
        pair<int, int> mxR = father[mxInd];
//        for (int itr : howMany[mxR]) {
        for (int _ = 0; _ < min(n - mxR.first - mxR.second, int(howMany[mxR].size())); ++_) {
            int itr = howMany[mxR][_];
            good[itr] = true;
        }
        mxInd = fatherInd[mxInd];
    }
    int bad = 0;
    for (int i = 1; i <= n; ++i) {
        if (not good[i]) {
            ++bad;
        }
    }

    cout << bad << ' ';
    for (int i = 1; i <= n; ++i) {
        if (not good[i]) {
            cout << i << ' ';
        }
    }
	return 0;
}
