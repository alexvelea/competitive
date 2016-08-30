#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f, kMaxN = 1e6+5;

int divisor[kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    for (int i = 2; i < kMaxN; i += 1) {
        if (divisor[i] == 0) {
            divisor[i] = i;
        } else {
            continue;
        }

        for (int64 j = 1LL * i * i; j < kMaxN; j += i) {
            divisor[j] = i;
        }
    }    

    int n, k; cin >> n >> k;
    unordered_map<int, int> result;
    for (int i = 1; i <= n; i += 1) {
        int x; cin >> x;
        unordered_map<int, int> mx;
        while (x != 1) {
            mx[divisor[x]] += 1;
            x /= divisor[x];
        }

        for (auto itr : mx) {
            result[itr.first] = max(result[itr.first], itr.second);
        }
    }

    unordered_map<int, int> mk;
    while (k != 1) {
        mk[divisor[k]] += 1;
        k /= divisor[k];
    }
    bool ok = true;
    for (auto itr : mk) {
        if (result[itr.first] < itr.second) {
            ok = false;}
    }

    if (ok) {
    cout << "Yes\n";} else {
    cout << "No\n";}
    return 0;
}
