#include <iostream>
using namespace std;

typedef long long int64;

const int kMaxN = 5e5+11;
const int64 kMaxVal = 3e10+5;

int64 right_up[kMaxN];
int64 right_down[kMaxN];
int64 down[kMaxN];
int64 diag[kMaxN];

int64 flow[kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i += 1) {
            cin >> right_up[i];
        }
        
        for (int i = 0; i < n; i += 1) {
            cin >> right_down[i];
        }

        right_down[n] = kMaxVal;

        for (int i = 0; i <= n; i += 1) {
            cin >> down[i];
            if (i != n) {
                cin >> diag[i];
            }
        }
    
        flow[0] = kMaxVal;
        for (int i = 0; i < n; i += 1) {
            flow[i + 1] = min(right_up[i], flow[i]);
            flow[i] -= flow[i + 1];
        }

        int64 remaining_down = kMaxVal;
        int64 result = 0;

        for (int i = n; i >= 0; i -= 1) {
            // go diag
            if (i != n) {
                auto d = min(
                    min(flow[i], diag[i]), 
                    remaining_down
                );
                remaining_down -= d;
                result += d;
                flow[i] -= d;
            }

            remaining_down = min(remaining_down, right_down[i]);

            auto d = min(
                min(flow[i], down[i]),
                remaining_down
            );
            remaining_down -= d;
            result += d;
            flow[i] -= d;

            if (i) {
                flow[i - 1] += flow[i];
            }
        }
        cout << result << '\n';
    }
}

