//Problem c @ 22-07-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 2e4 + 5, kMod = 1e9 + 7, kMaxH = 2e5 + 5;

#define int64 long long

int x[kMaxN], y[kMaxN];

int pow(int a, int p) {
    int rez = 1;
    while (p) {
        if (p & 1) {
            rez = (1LL * rez * a) % kMod;
        }
        a = (1LL * a * a) % kMod;
        p /= 2;
    }
    return rez;
}

int fact[kMaxH], invFact[kMaxH];

int dp[2][kMaxN];
pair<int, int> c[kMaxN];

int howMany(pair<int, int> a, pair<int, int> b) {
    if (a.first <= b.first and a.second <= b.second) {
        int x = (1LL * ((1LL * fact[b.first - a.first + b.second - a.second] * invFact[b.first - a.first]) % kMod) * 
        invFact[b.second - a.second]) % kMod;
//        cerr << "!!!\t" << a.first << '\t' << a.second << '\t' << b.first << '\t' << b.second << '\t' << x << '\n';
        return x;
    } else {
        if (a.first >= b.first and a.second >= b.second) {
            return howMany(b, a);
        } else {
            return 0;
        }
    }
}



int howMany(int a, int b, pair<int, int> c) {
    return howMany(make_pair(a, b), c);
}

int howMany(pair<int, int> a, int c, int d) {
    return howMany(c, d, a);
} 

int howMany(int a, int b, int c, int d) {
    return howMany(make_pair(a, b), make_pair(c, d));
}

void mod(int &a) {
    if (a < 0) {
        a += kMod;
    }
    if (a >= kMod) {
        a -= kMod;
    }
}

int main() {
	ios::sync_with_stdio(false);
    int h, w, n; cin >> h >> w >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i].first >> c[i].second;
    }
    sort(c + 1, c + n + 1); 
    ///////
    fact[0] = 1;
    for (int i = 1; i < kMaxH; ++i) {
        fact[i] = (1LL * fact[i - 1] * i) % kMod;
    }
    invFact[kMaxH - 1] = pow(fact[kMaxH - 1], kMod - 2);
    for (int i = kMaxH - 2; i; --i) {
        invFact[i] = (1LL * invFact[i + 1] * (i + 1)) % kMod;
    }
    invFact[0] = 1;
    ///////

    int rez = howMany(1, 1, h, w);
    for (int i = 1; i <= n; ++i) {
        dp[0][i] = howMany(1, 1, c[i]);
    }

    for (int i = 1; i <= n; ++i) {
//        cerr << dp[0][i] << '\t' << dp[1][i] << "<----\n";
        rez -= (1LL * dp[0][i] * howMany(c[i], h, w)) % kMod;
        rez += (1LL * dp[1][i] * howMany(c[i], h, w)) % kMod;
        mod(rez);
//        cerr << rez << ">??????\n";
        for (int j = i + 1; j <= n; ++j) {
            int exp = howMany(c[i], c[j]);
            if (exp) {
//                cerr << i << '\t' << j << '\n';
                dp[0][j] += (1LL * dp[1][i] * exp) % kMod;
                dp[1][j] += (1LL * dp[0][i] * exp) % kMod;
                mod(dp[0][j]);
                mod(dp[1][j]);
            }
        }
    }
    cout << rez << '\n';

	return 0;
}
