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
    vector<int> cost(n);
    for (int i = 0; i < n; i += 1) {
        cin >> cost[i];
    }

    vector<string> txt(n);
    for (int i = 0; i < n; i += 1) {
        cin >> txt[i];
    }

    int64 a = 0, b = cost[0];
    for (int i = 1; i < n; i += 1) {
        string q = txt[i];
        string w = txt[i];
        string z = txt[i - 1];
        string x = txt[i - 1];
        reverse(w.begin(), w.end());
        reverse(x.begin(), x.end());
        int64 na = 1LL * kInf * kInf, nb = 1LL * kInf * kInf;
        if (z <= q) {
            na = a;
        }
        if (x <= w) {
            nb = b + cost[i];
        }

        if (x <= q) {
            na = min(na, b);
        }

        if (z <= w) {
            nb = min(nb, a + cost[i]);
        }

        a = na;
        b = nb;
    }

    int64 r = min(a, b);
    if (r == 1LL * kInf * kInf) {
        cout << "-1\n";
    } else {
        cout << r << '\n';
    }
    return 0;
}
