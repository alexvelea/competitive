#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> el(n);
    for (int i = 0; i < n; i += 1) {
        cin >> el[i];
    }

    sort(el.begin(), el.end());
    reverse(el.begin(), el.end());
    int prev = el.front() + 1;

    int64 sum = 0;
    for (auto itr : el) {
        prev -= 1;
        prev = max(prev, 0);
        itr = min(itr, prev);
        sum += itr;
        prev = itr;
    }
    cout << sum << '\n';
}

