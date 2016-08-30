#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;

int64 T(int64 n) {
    int64 result = 0;
    for (int i = 2; 1LL * i * i * i <= n; i += 1) {
        int64 x = 1LL * i * i * i;
        result += n / x;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    int64 m; cin >> m;
    int64 n = 0;
    for (int p = 55; p >= 0; p -= 1) {
        if (T((1LL << p) + n) < m) {
            n += 1LL << p;
        }
    }

    if (T(n + 1) != m) {
        cout << "-1\n";
    } else {
        cout << n + 1 << '\n';
    }
    return 0;
}
