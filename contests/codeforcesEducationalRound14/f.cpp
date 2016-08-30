#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f, kMaxN = 3e6+5;

int ap[kMaxN];
vector<int64> sp(kMaxN + 5, 0);
vector<int64> result(kMaxN + 5, 0);

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        int x; scanf("%d", &x);
        ap[x] += 1;
        sp[x] += 1;
    }

    reverse(sp.begin(), sp.end());
    int64 last = 0;
    for (auto& itr : sp) {
        itr += last;
        last = itr;
    }
    reverse(sp.begin(), sp.end());

    for (int i = 1; i < kMaxN; i += 1) {
        int cnt = ap[i];
        if (1LL * i * i > kMaxN) {
            result[kMaxN - 1] += 1LL * cnt * (cnt - 1) / 2;
        } else {
            result[i * i] += 1LL * cnt * (cnt - 1) / 2;
        }

        int j = i + 1;
        while (1LL * i * j < kMaxN) {
            result[i * j] += ap[i] * ap[j];
            j += 1;
        }
        result[kMaxN - 1] += 1LL * ap[i] * sp[j];
    }
    
    reverse(result.begin(), result.end());
    last = 0;
    for (auto& itr : result) {
        itr += last;
        last = itr;
    }
    reverse(result.begin(), result.end());

    int q; scanf("%d", &q);
    vector<int> Q(q);
    for (int i = 0; i < q; i += 1) {
        scanf("%d", &(Q[i]));
    }

    for (auto itr : Q) {
        cout << 2LL * result[itr] << '\n';
    }
    return 0;
}
