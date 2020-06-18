#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxD = 1e9;
const int kMiss = 0;
const int kHit = 1;
const int kCenter = 2;

bool found = false;

int throwHit(int x, int y) {
    if (x < -kMaxD || x > kMaxD || y < -kMaxD || y > kMaxD) {
        return kMiss;
    }

    if (found) { return kMiss; }
    cout << x << ' ' << y << endl;
    string ans; cin >> ans;
    if (ans == "HIT") { return kHit; }
    if (ans == "MISS") { return kMiss; }
    if (ans == "CENTER") { 
        found = true;
        return kCenter; 
    }
    assert(false);
}


int throwHit(pair<int, int> x) {
    return throwHit(x.first, x.second);
}

pair<int, int> findOne() {
    for (pair<int, int> x : vector<pair<int, int>>({
                {0, 0}, 
                {-kMaxD/2, -kMaxD/2}, {-kMaxD/2, +kMaxD/2}, {+kMaxD/2, +kMaxD/2}, {+kMaxD/2, -kMaxD/2},
                {0, -kMaxD/2}, {0, +kMaxD/2}, {+kMaxD/2, 0}, {-kMaxD/2, 0}
                })) {
        if (throwHit(x) != kMiss) {
            return x;
        }
    }

    assert(0);
}

pair<int, int> go(pair<int, int> o, pair<int, int> d) {
    pair<int, int> ans= o;
    for (int l = 29; l >= 0; l -= 1) {
        if (throwHit(ans.first + (1 << l) * d.first, ans.second + (1 << l) * d.second)) {
            ans = {ans.first + (1 << l) * d.first, ans.second + (1 << l) * d.second};
        }
    }

    return ans;
}

pair<int, int> goUp(pair<int, int> o) {
    return go(o, {-1, 0});
}

pair<int, int> goDown(pair<int, int> o) {
    return go(o, {+1, 0});
}

pair<int, int> goLeft(pair<int, int> o) {
    return go(o, {0, -1});
}

pair<int, int> goRight(pair<int, int> o) {
    return go(o, {0, +1});
}

void BrutforceNearby(pair<int, int> o, int d) {
    for (int i = -d; i <= d; i += 1) {
        for (int j = -d; j <= d; j += 1) {
            throwHit(o.first + i, o.second + j);
        }
    }
}

void solve() {
    auto one = findOne();
    auto up = goUp(one);
    auto down = goDown(one);
    pair<int, int> center = {int((1LL * up.first + down.first) / 2), int((1LL * up.second + down.second) / 2)};
    auto left = goLeft(center);
    auto right = goRight(center);
    pair<int, int> ans = {int((1LL * left.first + right.first) / 2), int((1LL * left.second + right.second) / 2)};
    
    BrutforceNearby(ans, 2);
}

int main() {
    int T; cin >> T;
    int a, b; cin >> a >> b;

    for (int t = 1; t <= T; t += 1) {
        found = false;
        solve();
    }
}
