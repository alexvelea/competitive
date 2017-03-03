#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int remaining = 4 * 60;
    int n, k; cin >> n >> k;
    int solved = 0;
    remaining -= k;
    for (int i = 1; i <= n; i += 1) {
        if (remaining - 5 * i >= 0) {
            solved += 1;
            remaining -= 5 * i;
        } else {
            break;
        }
    }
    cout << solved << '\n';
    return 0;
}
