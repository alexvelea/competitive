#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f, kMaxN = 1e6+5;

int not_prime[kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    for (int i = 2; i * i < kMaxN; i += 1) {
        if (not_prime[i]) {
            continue;
        }

        for (int j = i * i; j < kMaxN; j += i) {
            not_prime[j] = true;
        }
    }
    
    int n; cin >> n;
    for (int i = 1; i; i += 1) {
        if (not_prime[n * i + 1]) {
            cout << i << '\n';
            exit(0);
        }
    }


    return 0;
}
