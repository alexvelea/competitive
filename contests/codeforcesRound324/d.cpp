//Problem d @ 06-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

bool isPrime(int a) {
    if (a < 2) {
        return false;
    }
    for (int d = 2; d * d <= a; ++d) {
        if (a % d == 0) {
            return false;
        }
    }
    return true;
}

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
	if (isPrime(n)) {
        cout << 1 << ' ' << n << '\n';
        return 0;
    }
    if (isPrime(n - 2)) {
        cout << 2 << ' ' << 2 << ' ' << n - 2 << '\n';
        return 0;
    }
    cout << 3 << '\n';
    for (int p = n - 1; p; --p) {
        int s = n - p;
        if (isPrime(p) == false) {
            continue;
        }
        for (int a = 3; a <= s; ++a) {
            if (isPrime(a) == false) {
                continue;
            }
            if (isPrime(s - a)) {
                cout << p << ' ' << a << ' ' << s - a << '\n';
                return 0;
            }
        }
    }

    return 0;
}
