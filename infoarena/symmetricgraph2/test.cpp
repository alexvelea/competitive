#include <iostream>
#include <vector>
using namespace std;
int main() {
    srand(time(NULL));
    int n; cin >> n;
    vector<int> has_child(n + 1, 0);
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; i += 1) {
        int parent = rand() % (i - 1) + 1;
        has_child[parent] = true;
        edges.push_back({parent, i});
    }

    for (int i = 0; i + 1 < n; i += 1) {
        edges.push_back({2 * n - edges[i].first + 1, 2 * n - edges[i].second + 1});
    }

    for (int i = 1; i <= n; i += 1) {
        if (has_child[i] == false) {
            edges.push_back({i, 2 * n - i + 1});
        }
    }

    cout << 2 * n << ' ' << edges.size() << '\n';
    for (auto itr : edges) {
        cout << itr.first << ' ' << itr.second << ' ' << 1 << '\n';
    }
    return 0;
}
