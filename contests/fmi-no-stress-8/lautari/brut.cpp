#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> els(n);
    for (int i = 0; i < n; i += 1) {
        cin >> els[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i += 1) {
        map<int, int> viz;
        for (int j = i; j < n; j += 1) {
            viz[els[j]] += 1;
            if (viz.size() >= l and viz.size() <= r) {
                ans += 1;
            }
        }
    }

    cout << ans << '\n';
}
