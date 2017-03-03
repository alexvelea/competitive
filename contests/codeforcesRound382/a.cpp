#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxN = 5e3;

int best[kMaxN];

int cost(int i) {
    for (int j = 2; j * j <= i; j += 1) {
        if (i % j == 0) {
            return i / j;
        }
    }
    return 1;
}

int main() {
    best[1] = 1e9;
    best[2] = 1;
    best[3] = 1;
    for (int i = 4; i < kMaxN; i += 1) {
        best[i] = i;
        for (int taken = 2; taken + 1 <= i; taken += 1) {
            best[i] = min(best[i - taken] + cost(taken), best[i]);
            best[i] = min(best[i - taken] + best[taken], best[i]);
        }
    }
    
    vector<int> fibo(1e5, false);
    vector<int> primes;
    for (int i = 2; i * i < (int)1e5; i += 1) {
        if (fibo[i]) {
            continue;
        }
        for (int j = i * i; j < (int)1e5; j += i) {
            fibo[j] = true;
        }
    }

    for (int i = 2; i < 1e5; i += 1) {
        if (not fibo[i]) {
            primes.push_back(i);
        }
    }

    int n; cin >> n;
    int cost = 0;
    while (n >= kMaxN) {
        while (1LL * primes.back() * primes.back() > n) {
            primes.pop_back();
        }
        int q = primes.back();
        cost += 1;
        n -= 1LL * q * q;
    }
    cost += best[n];
    cout << cost << '\n';
    return 0;
}
