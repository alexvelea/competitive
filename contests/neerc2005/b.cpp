//Problem b @ 14-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-7;

#define int64 long long

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    int64 sum;
    while (m--) {
        int s; cin >> s;
        sum += s;
    }
    cout << sum % n;
	return 0;
}
