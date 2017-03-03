#include <iostream>
using namespace std;

int perm[100], ord[4];

int Val(int l, int r) {
    int mx = perm[l], mn = perm[l];
    for (int i = l; i < r; i += 1) {
        mx = max(perm[i], mx);
        mn = min(perm[i], mn);
    }

    if (mx - mn + 1 != r - l) {
        return -1;
    }

    return mn;
}

int main() {
    int n, ans;
    while (cin >> n) {
        ans = 0;
        for (int i = 0; i < n; i += 1) {
            cin >> perm[i];
        }

        for (int i = 0; i < 4; i += 1) {
            cin >> ord[i];
        }

        for (int a = 0; a < n; a += 1) {
        for (int b = a + 1; b < n; b += 1) {
        for (int c = b + 1; c < n; c += 1) {
            int v[4];
            v[0] = Val(0, a);
            v[1] = Val(a, b);
            v[2] = Val(b, c);
            v[3] = Val(c, n);

            int ok = true;
            for (int i = 0; i < n; i += 1) {
                if (v[i] == -1) {
                    ok = false;
                }
            }

            for (int i = 0; i < 4; i += 1) {
                for (int j = i + 1; j < 4; j += 1) {
                    if ((v[i] - v[j]) * (ord[i] - ord[j]) <= 0) {
                        ok = false;
                    }
                }
            }

            if (ok) {
                ans += 1;
                cerr << a << ' ' << b << ' ' << c << '\n';
            }
        }
        }
        }

        cout << ans << '\n';
    }
}

