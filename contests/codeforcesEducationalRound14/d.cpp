#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f, kMaxN=1e6;

vector<int> edges[kMaxN];

int main() {
    ios_base::sync_with_stdio(false);
    int n, p; cin >> n >> p;
 
    vector<int> element(n + 1, 0);
    vector<int> visited(n + 1, false);
    vector<int> result(n + 1, 0);

    for (int i = 1; i <= n; i += 1) {
        cin >> element[i];
    }

    for (int i = 0; i < p; i += 1) {
        int a, b; cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for (int i = 1; i <= n; i += 1) {
        if (visited[i] == true) {
            continue;
        }

        vector<int> indices;
        vector<int> values;

        vector<int> bfs = {i};
        visited[i] = true;
 
        indices.push_back(i);
        values.push_back(element[i]);
        
        while (bfs.size()) {
            int nod = bfs.back();
            bfs.pop_back();
            for (auto itr : edges[nod]) {
                if (visited[itr]) {
                    continue;
                }

                visited[itr] = true;
                values.push_back(element[itr]);
                indices.push_back(itr);

                bfs.push_back(itr);
            }
        }

        sort(indices.begin(), indices.end());
        sort(values.begin(), values.end());
        reverse(values.begin(), values.end());

        for (int i = 0; i < (int)indices.size(); i += 1) {
            result[indices[i]] = values[i];
        }
    }

    for (int i = 1; i <= n; i += 1) {
        cout << result[i] << ' ';
    }
    return 0;
}
