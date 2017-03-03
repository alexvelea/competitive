#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

void Answer(const vector<pair<int, int>>& edges) {
    cout << edges.size() << '\n';
    for (auto itr : edges) {
        cout << itr.first << ' ' << itr.second << '\n';
    }
    exit(0);
}

void NoAns() {
    cout << "-1\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, k; cin >> n >> k;
    if (n == 2) {
        NoAns();
    }

    if (n == 4 and k == 2) {
        NoAns();
    }

    if (n == 4 and k == 3) {
        Answer({{1, 2}, {2, 3}, {3, 4}});
    }

    if (n <= 4) {
        NoAns();
    }

    if (k == 2) {
        vector<pair<int, int>> edges;
        edges.push_back({1, 2});
        edges.push_back({1, 3});
        edges.push_back({4, 3});
        for (int i = 5; i <= n; i += 1) {
            edges.push_back({4, i});
        }

        Answer(edges);
    }

    if (k == 3) {
        vector<pair<int, int>> edges;
        edges.push_back({1, 2});
        edges.push_back({2, 3});
        for (int i = 3; i <= n; i += 1) {
            for (int j = i + 1; j <= n; j += 1) {
                edges.push_back({i, j});
            }
        }
        Answer(edges);
    }
    NoAns();
    return 0;
}
