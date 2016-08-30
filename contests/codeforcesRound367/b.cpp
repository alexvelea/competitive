#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> values(n + 1);
    for (int i = 0; i < n; i += 1) {
        cin >> values[i];
    }
    values[n] = +kInf;
    sort(values.begin(), values.end());
    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << upper_bound(values.begin(), values.end(), x) - values.begin() << '\n';
    }
    return 0;
}
