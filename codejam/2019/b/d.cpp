#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int kMod = 1e9+7;

int to[105][2];
int sum[105];
int added[105];
int start[105];

void Add(int& a, int b) {
    a += b;
    if (a >= kMod) {
        a -= kMod;
    }
}

int n;

bool skip_one = false;

void DoSteps() {
    vector<int> next_sum(n + 1);
    vector<int> next_added(n + 1);

    if (skip_one) {
        next_sum[1] = sum[1];
    }

    for (int i = 1 + skip_one; i <= n; i += 1) {
        if (added[i] == 0) {
            continue;
        }

        for (int j = 0; j < 2; j += 1) {
            Add(next_sum[to[i][j]], sum[i]);
            next_added[to[i][j]] = 1;
        }
    }

    for (int i = 1; i <= n; i += 1) {
        sum[i] = next_sum[i];
        added[i] = next_added[i];
    }
}


int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; T += 1) {

        cin >> n;

        if (n > 100) {
            return 0;
        }

        for (int i = 1; i <= n; i += 1) {
            for (int j = 0; j < 2; j += 1) {
                cin >> to[i][j];
            }
        }

        for (int i = 1; i <= n; i += 1) {
            cin >> sum[i];
            start[i] = sum[i];
            added[i] = (sum[i] != 0);
        }

        bool ok = true;
        for (int p = 0; p < 2; p += 1) {
            skip_one = p;

            for (int i = 1; i <= n; i += 1) {
                sum[i] = start[i];
                added[i] = (sum[i] != 0);
            }

            map<int, int> viz;
            // do steps
            for (int i = 0; i < 1000; i += 1) {
                DoSteps();
                viz[sum[1]] = 1;
            }

            for (int i = 0; ok && i < 1000; i += 1) {
                DoSteps();
                if (viz[sum[1]] == 0) {
                    ok = false;
                }
            }
        }

        if (ok) {
            cout << "Case #" << T << ": " << sum[1] << '\n';
        } else {
            cout << "Case #" << T << ": UNBOUNDED\n";
        }
    }

    return 0;
}
