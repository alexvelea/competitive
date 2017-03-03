#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    map<string, int> pa, pb;
    for (int i = 0; i < n; i += 1) {
        string x; cin >> x;
        pa[x] = 1;
    }

    for (int i = 0; i < m; i += 1) {
        string x; cin >> x;
        pb[x] = 1;
    }

    int shared = 0;
    for (auto itr : pa) {
        if (pb[itr.first] == 1) {
            shared += 1;
        }
    }

    int a = n - shared;
    int b = m - shared;
    a += shared & 1;
    if (a > b) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
