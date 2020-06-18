#include <iostream>
using namespace std;

const int kMaxN = 1e5+1;

pair<int, int> children[kMaxN];

int main() {
    int n, extra_depth;
    cin >> n >> extra_depth;

    auto Add = [&](int father, int son) {
        if (children[father].first == 0) {
            children[father].first = son;
        } else {
            children[father].second = son;
        }
    };

    for (int i = 2; i <= extra_depth; i += 1) {
        Add(i - 1, i);
    }

    for (int i = 2; i <= n; i += 1) {
        Add(extra_depth - 1 + i / 2, extra_depth - 1 + i);
    }

    cout << n << ' ' << 1 << ' ' << 1000000000 << '\n';
    for (int i = 1; i <= n; i += 1) {
        cout << children[i].first << ' ' << children[i].second << '\n';
    }
}
