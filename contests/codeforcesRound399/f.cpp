#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 2e5+5, kMod = 1e9+7;

int fact[kMaxN];
int inv_fact[kMaxN];

int Pow(int a, int p) {
    int r = 1;
    while (p) {
        if (p & 1) {
            r = (1LL * r * a) % kMod;
        }
        a = (1LL * a * a) % kMod;
        p /= 2;
    }
    return r;
}

int Comb(int a, int b) {
    if (a < b) {
        return Comb(b, a);
    }

    return 1LL * fact[a] * inv_fact[b] % kMod * inv_fact[a - b] % kMod;
}

void Init() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < kMaxN; i += 1) {
        fact[i] = (1LL * fact[i - 1] * i) % kMod;
        inv_fact[i] = Pow(fact[i], kMod - 2);
    }
}

int Count(int sum, int num_b, int min_el) {
    if (1LL * min_el * num_b > sum) {
        return 0;
    }

    return Comb(sum - num_b * min_el + num_b - 1, num_b - 1);
}

int Solve(int min_el, int a, int b) {
    vector<int> apa(kMaxN, 0);    
    vector<int> apb(kMaxN, 0);    
    for (int l = 1; l < kMaxN; l += 1) {
        apa[l] = Count(a, l, 1);
    }

    for (int l = 1; l < kMaxN; l += 1) {
        apb[l] = Count(b, l, min_el);
    }

    long long result = 0;
    if (a == 0) {
        return apb[1];
    } else if (b == 0) {
        return apa[1];
    }

    for (int l = 1; l + 1 < kMaxN; l += 1) {
        result += 2LL * apa[l] * apb[l] % kMod;
        result += 1LL * apa[l + 1] * apb[l] % kMod;
        result += 1LL * apa[l] * apb[l + 1] % kMod;
        result %= kMod;
    }

    return result;
}

int main() {
    Init();
    ios_base::sync_with_stdio(false);
 
    int f, w, h; cin >> f >> w >> h;
    int a = Solve(1, f, w);
    int b = Solve(h + 1, f, w);

    cout << (1LL * b * Pow(a, kMod - 2)) % kMod << '\n';
    return 0;
}
