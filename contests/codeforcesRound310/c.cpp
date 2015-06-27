//Problem c @ 27-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 2e5 + 5, inf = 0x3f3f3f3f;

#define int64 long long

pair<int, int> aint[4 * kMaxN];
pair<int, char> query[kMaxN];
bool viz[kMaxN];

int aintQuery(int nod, int st, int dr, int where, int ind) {
    if (st == dr and st == where) {
        if (ind == 0) {
            return aint[nod].first;
        } else {
            return aint[nod].second;
        }
    }

    int mid = (st + dr) / 2;
    if (where <= mid) {
        if (ind == 0) {
            return min(aint[nod].first, aintQuery(2 * nod, st, mid, where, ind));
        } else {
            return max(aint[nod].second, aintQuery(2 * nod, st, mid, where, ind));
        }
    } else {
        if (ind == 0) {
            return min(aint[nod].first, aintQuery(2 * nod + 1, mid + 1, dr, where, ind));
        } else {
            return max(aint[nod].second, aintQuery(2 * nod + 1, mid + 1, dr, where, ind));
        }
    }
}

void aintUpdate(int nod, int st, int dr, int c1, int c2, int val, int ind) {
    if (c1 <= st and dr <= c2) {
        if (ind == 0) {
            aint[nod].first = min(aint[nod].first, val); 
        } else {
            aint[nod].second = max(aint[nod].second, val);
        }
        return ;
    }
    
    if (c2 < st or dr < c1) {
        return ;
    } 

    int mid = (st + dr) / 2;
    aintUpdate(2 * nod, st, mid, c1, c2, val, ind);
    aintUpdate(2 * nod + 1, mid + 1, dr, c1, c2, val, ind);
}
 

int main() {
	ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<int> uniq;
    uniq.push_back(-inf);
    uniq.push_back(n + 1);
    uniq.push_back(0);
    
    for (int i = 1; i <= q; ++i) {
        int aux; cin >> query[i].first >> aux >> query[i].second;
        uniq.push_back(query[i].first);
    }
    sort(uniq.begin(), uniq.end());
    uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
    n = int(uniq.size()) - 1;
    
    for (int i = 1; i < 4 * n; ++i) {
        aint[i].first = n;
        aint[i].second = 1;
    }
    
    for (int i = 1; i <= q; ++i) {
        int where = lower_bound(uniq.begin(), uniq.end(), query[i].first) - uniq.begin();
        if (viz[where]) {
            cout << 0 << '\n';
            continue;
        }
        viz[where] = true;

        int c = query[i].second;
        if (c == 'U') {
            int rez = aintQuery(1, 1, n, where, 0); 
            cout << uniq[rez] - uniq[where] << '\n';
//            cerr << where << "@@@\t" << rez << '\n';
            aintUpdate(1, 1, n, where, rez, where, 1);
        } else {
            int rez = aintQuery(1, 1, n, where, 1);
            cout << uniq[where] - uniq[rez] << '\n';
//            cerr << where << "#####\t" << rez << '\n';
            aintUpdate(1, 1, n, rez, where, where, 0);
        }
    }
	return 0;
}
