#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n = 50;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; i += 1) {
/*        
        if (i % 7 != 0) {
            continue;
        }
        for (int j = 1; j <= 7 + rand() % 6; j += 1) {
            edges.push_back({i, i - j});
        }
*/
        if (i % 13 != 0) {
            continue;
        }
        for (int j = 1; j <= 13; j += 1) {
            edges.push_back({i, i - j});
        }
    }

    cout << n << ' ' << edges.size() << '\n';
    for (auto itr : edges) {
        cout << itr.first << '\t' << itr.second << '\n';
    }
}
