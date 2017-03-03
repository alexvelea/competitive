#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    int mn = +2e9;
    int mx = -2e9;
    vector<int> el(n);
    for (auto& itr : el) {
        cin >> itr;
        mn = min(mn, itr);
        mx = max(mx, itr);
    }

    int result = 0;
    for (auto itr : el) {
        if (mn < itr and itr < mx) {
            result += 1;
        }
    }

    cout << result << '\n';
    return 0;
}
