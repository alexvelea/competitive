#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, kMaxN = 1e5+5;

int prime[kMaxN], digit[kMaxN], result[kMaxN];

int main() {
    prime[1] = 1;
    for (int i = 2; i < kMaxN; i += 1) {
        if (prime[i] != 0) {
            continue;
        }

        for (int j = i; j < kMaxN; j += i) {
            prime[j] += 1;
        }
    }
    for (int a = 1, b = 10, c = 1; a < kMaxN; a *= 10, b *= 10, c += 1) {
        for (int i = a; i < b and i < kMaxN; i += 1) {
            digit[i] = c;
        }
    }

    for (int i = 0; i < kMaxN; i += 1) {
        if (digit[i] == prime[i]) {
            result[i] += 1;    
        } 
    }

    for (int i = 1; i < kMaxN; i += 1) {
        result[i] += result[i - 1];
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        cout << result[b] - result[a - 1] << '\n';
    }
}
