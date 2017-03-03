#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    cout << "YES\n";
    for (int i = 0; i < n; i += 1) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        int p = c & 1;
        int q = b & 1;
        cout << p * 2 + q + 1 << '\n';
    }
    return 0;
}
