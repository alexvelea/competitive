//Problem e @ 16-06-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include <cassert>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 5 * 1e5 + 25, kSize = 200;

#define int64 long long
unordered_map<int, int> inside[kMaxN / kSize + 5];
int lazy[kMaxN / kSize + 5];

int el[kMaxN];


void Add(int st, int dr, int val) {
    for (int b = 0, c1 = 0, c2 = kSize - 1; c1 <= dr; c1 += kSize, c2 += kSize) {
        if (st <= c1 and c2 <= dr) {
            lazy[b] += val;
            lazy[b] = min(lazy[b], inf);
        } else {
            int s = max(c1, st);
            int d = min(c2, dr);
            while (s <= d) {
                int x = el[s];
                inside[b][x]--;
                x += val;
                x = min(x, inf);

                el[s] = x;
                inside[b][x]++;
                ++s;
            }
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> el[i];
        inside[i / kSize][el[i]]++;
    }
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int st, dr, x; cin >> st >> dr >> x;
            st--;
            dr--;
            Add(st, dr, x);
        } else {
            int val; cin >> val;
            int c1 = 0, c2 = -1;
            for (int b = 0; b <= n / kSize; ++b) {
                if (inside[b][val - lazy[b]] != 0) {
                    c1 = b * kSize;
                    while (c1 < (b + 1) * kSize and el[c1] + lazy[b] != val) {
                        ++c1;
                    }
                    assert(c1 != (b + 1) * kSize);
                }
            }

            for (int b = n / kSize + 1; b >= 0; --b) {
                if (inside[b][val - lazy[b]] != 0) {
                    c2 = min((b + 1) * kSize - 1, n - 1); 
                    while (c2 >= b * kSize and el[c2] + lazy[b] != val) {
                        --c2;
                    }
                    assert(c2 != b * kSize - 1);
                }
            }
            cout << c2 - c1 << '\n';
        }
    }

	return 0;
}
