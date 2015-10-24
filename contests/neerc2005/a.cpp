#include <iostream>
#include <algorithm>
#include <vector>s
#define N 1010

using namespace std;
vector<pair<int,int> > v[N];

int d[N], c[N], D[N][N], b[N], C[N][N], T[N][N], n, x, y, k, p;
int main () {
    cin >> n >> k >> p;

    for (int i = 1; i <= k; ++i) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> x >> y;
        v[y].push_back(make_pair(x, i));
    }
    for (int i = 1; i <= n; ++i) {
        d[i] = 1<<29;
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            D[i][j] = 1<<30;
        }
        int sum = b[i];
        sort(v[i].begin(), v[i].end());
        for (int tk = 1; tk <= v[i].size(); ++tk) {
            sum += v[i][tk - 1].first;
            for (int j = n - tk; j >= 0; --j) {
                if (d[j] + sum < D[i][j + tk]) {
                    D[i][j + tk] = d[j] + sum;
                    C[i][j + tk] = c[j];
                    T[i][j + tk] = tk;
                }
            }
        }
        for (int j = 1; j <= n; ++j) {
            if (D[i][j] < d[j]) {
                d[j] = D[i][j];
                c[j] = i;
            }
        }
    }
    for (int i = n; i >= 0; --i) {
        if (d[i] <= p) {
            cout << i << "\n";
            int j = c[i];
            while (i) {
                for (int k = 1; k <= T[j][i]; ++k) {
                    cout << v[j][k - 1].second << " ";
                }
                int ni = i - T[j][i];
                int nj = C[j][i];
                j = nj;
                i = ni;
            }

            break;
        }
    }
    return 0;
}
