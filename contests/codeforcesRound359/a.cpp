#include <iostream>
using namespace std;

typedef long long int64;

int main() {
    int n; int64 x; cin >> n >> x;
    int result = 0;
    for (int i = 1; i <= n; i += 1) {
        char c; cin >> c;
        int p; cin >> p;
        if (c == '+') {
            x += p;
        } else {
            if (p <= x) {
                x -= p;
            } else {
                result += 1;
            }
        }
    }
    cout << x << '\t' << result << '\n';
    return 0;
}
