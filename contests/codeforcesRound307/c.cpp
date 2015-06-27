//Problem c @ 16-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1e5 + 5;
const double eps = 1e-7;

#define int64 long long

int remaining[kMaxN], el[kMaxN];

bool possible(int64 t, int n, int m) {
    for (int i = 1; i <= n; ++i) {
        remaining[i] = el[i];
    }
    while (m > 0) {
        int64 x = t - n;
        while ((x > 0 and n != 0) or (n != 0 and remaining[n] == 0)) {
            if (remaining[n] <= x) {
                x -= remaining[n];
                --n;
            } else {
                remaining[n] -= x;
                x = 0;
            }
        }

        if (n == 0) {
            return true;
        }
        --m;
    }
    return false;
}

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> el[i];
    }
    
    while (el[n] == 0 and n) {
        --n;
    }

    int64 rez = -1;
    for (int p = 50; p >= 0; --p) {
        if (not possible((1LL << p) + rez, n, m)) {
            rez += (1LL << p);
        }
    }
    cout << rez + 1 << '\n';
	return 0;
}
