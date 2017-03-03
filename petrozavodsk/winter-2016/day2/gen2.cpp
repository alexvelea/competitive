#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n = 50;
    vector<pair<int, int>> edges;
    for (int i = 1; i + 1< n; i += 1) {
        edges.push_back({i, i + 2});
    }
    edges.push_back({n, n - 1});

    cout << n << ' ' << edges.size() << '\n';
    for (auto itr : edges) {
        cout << itr.first << '\t' << itr.second << '\n';
    }
}
