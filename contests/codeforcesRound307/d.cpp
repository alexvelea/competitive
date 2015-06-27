//Problem d @ 16-06-2015
#include <array>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

int mod;
int64 n, k, l;


int64 P(int64 a, int64 p) {
    a = a % mod;
    int64 rez = 1;
    while (p) {
        if (p & 1) {
            rez = (1LL * rez * a) % mod;
        }
        a = (1LL * a * a) % mod;
        p /= 2;
    }
    return rez;
}

array<int64, 4> inm(array<int64, 4> a, array<int64, 4> b) {
    array<int64, 4> rez;
    for (int i = 0; i < 4; ++i) {
        rez[i] = 0;
    }

    for (int l = 0; l < 2; ++l) {
        for (int c = 0; c < 2; ++c) {
            for (int x = 0; x < 2; ++x) {
                rez[l * 2 + c] += (1LL * a[l * 2 + x] * b[x * 2 + c]) % mod;
                rez[l * 2 + c] %= mod;
            }
        }
    }
    return rez;
}

array<int64, 4> matPow(array<int64, 4> a, int64 p) {
    array<int64, 4> rez;
    rez[0] = 1;
    rez[1] = 0;
    rez[2] = 0;
    rez[3] = 1;
    while (p) {
        if (p & 1) {
            rez = inm(rez, a);
        }
        a = inm(a, a);
        p /= 2;
    }
    return rez;
}

int main() {
	ios::sync_with_stdio(false);
    cin >> n >> k >> l >> mod;

    int64 maxK = 0;
    if (l == 0) {
        maxK = 0;
    } else {
        maxK = (1LL << (l - 1));
        maxK--;
        maxK += (1LL << (l - 1));
    }


    if (l != 64 and maxK < k) {
        cout << 0;
        return 0;
    }

    int64 p = 0;
    while (k) {
        ++p;
        k -= k & (-k);
    }

    int64 good = P(2LL, n);
    
    array<int64, 4> aux; aux[0] = 0; aux[1] = 1; aux[2] = 1; aux[3] = 1;

    array<int64, 4> fin = matPow(aux, n - 1);
    int64 bad = (fin[0] + fin[1] + fin[2] + fin[3]) % mod;
    
    good = good - bad + mod;
    good %= mod;
    int64 rez = P(good, p);
    rez = (1LL * rez * P(1LL * bad, 1LL * (l - p))) % mod;
    cout << rez << '\n';

	return 0;
}
