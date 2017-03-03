#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f, kMaxN = 1e6+5;

int aib[kMaxN], aib_inside = 0;
int n, k;

int AibQuery(int pos) {
    int result = 0;
    while (pos) {
        result += aib[pos];
        pos -= pos & (-pos);
    }
    return result;
}

int AibQuery(int left, int right) {
    if (right > n) {
        return AibQuery(left, right - n);
    } else if (left <= 0) {
        return AibQuery(left + n, right);
    }

//    cerr << left << '\t' << right << '\n';
    if (1 <= left and left <= right and right <= n) {
        return AibQuery(right) - AibQuery(left - 1);   
    } else if (right < left) {
        return aib_inside - AibQuery(left - 1) + AibQuery(right);
    } else {
        assert(0);
        return 0;
    }
}

void AibUpdate(int pos, int value) {
    aib_inside += value;
    while (pos < kMaxN) {
        aib[pos] += value;
        pos += (pos) & (-pos);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int64 ans = 1;   

    cin >> n >> k;
    k = min(k, n - k);

    for (int i = 0; i < n; i += 1) {
        int pos = (1LL * i * k) % n + 1;

        ans += AibQuery(pos, pos + k - 1);
        ans += AibQuery(pos - k + 1, pos);
        AibUpdate(pos, +1);

        ans += 1;
        cout << ans << ' ';
    }

    return 0;
}
