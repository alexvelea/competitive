#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n; cin >> n;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i += 1) {
        int x; 
        cin >> x;
        events.push_back({x, i});
    }

    sort(events.begin(), events.end());
    vector<int> el(n + 1, 0);

    for (int i = 0; i < n; i += 1) {
        el[events[i].second] = i + 1;
    }

    for (int i = 1; i <= n; i += 1) {
        for (int j = n; j > i; j -= 1) {
            if (el[j] == i) {
                cout << j - 1 << ' ' << j << '\n';
                swap(el[j], el[j - 1]);
            }
        }
    }

    return 0;
}
