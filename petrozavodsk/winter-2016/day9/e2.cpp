#include <iostream>
using namespace std;

typedef long long int64;

const int kMaxN = 5e5+5;
const int64 kMaxVal = 3e9+5;

int64 right_up[kMaxN];
int64 right_down[kMaxN];
int64 down[kMaxN];
int64 diag[kMaxN];

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

        right_up[n] = kMaxVal;
        right_down[n] = kMaxVal;

        for (int i = 0; i <= n; i += 1) {
            cin >> down[i];
            if (i != n) {
                cin >> diag[i];
            }
        }

        for (int i = n - 1; i >= 0; i -= 1) {
            right_down[i] = min(right_down[i], right_down[i + 1]);
        }
    
        int64 result = 0;

        int64 put_down = 0;
        int64 flow = kMaxVal;

        for (int i = 0; i <= n; i += 1) {
            // go down
            {
                auto d = min(
                    min(down[i], flow),
                    right_down[i] - put_down
                );

                flow -= d;
                put_down += d;
                result += d;
            }

            if (i != n) {
                auto d = min(
                    min(diag[i], flow),
                    right_down[i + 1] - put_down
                );

                flow -= d;
                put_down += d;
                result += d;
            
                flow = min(flow, right_up[i]);
            }
        }
        cout << result << '\n';
    }
}

