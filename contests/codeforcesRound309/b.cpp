//Problem b @ 25-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

int64 howMuch[55];

int main() {
	ios::sync_with_stdio(false);
    howMuch[0] = 1;
    howMuch[1] = 1;
    for (int i = 2; i <= 50; ++i) {
        howMuch[i] = howMuch[i - 1] + howMuch[i - 2];
    }
    int n; int64 k; cin >> n >> k;
    for (int i = 1, r = n; i <= n; ) {
        if (howMuch[r - 1] >= k) {
            cout << i << ' ';
            --r;
            ++i;
        } else {
            k -= howMuch[r - 1];
            cout << i + 1 << ' ' << i << ' ';
            i += 2;
            r -= 2;
        }
    }
	return 0;
}
