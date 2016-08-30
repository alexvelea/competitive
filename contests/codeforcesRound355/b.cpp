#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n, h, k; cin >> n >> h >> k;
    int64 result = 0;
    int inside = 0;
    for (int i = 0; i < n; i += 1) {
        int x; cin >> x;
        int required_time = 1LL * (inside + x - h + k - 1) / k;
        if (required_time > 0) {
            result += required_time;
            inside -= k * required_time;
            inside = max(inside, 0);
        }
        inside += x;
    }
    result += (inside + k - 1) / k;
    cout << result << '\n';
    return 0;
}
