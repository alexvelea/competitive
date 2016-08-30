#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> a(n + 1, 0), min_dist(n + 1, +inf);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    
    min_dist[1] = 0;
    queue<int> q;
    q.push(1);

    while (q.size()) {
        int nod = q.front();
        q.pop();

        if (nod != n and min_dist[nod + 1] > min_dist[nod] + 1) {
            min_dist[nod + 1] = min_dist[nod] + 1;
            q.push(nod + 1);
        }

        if (nod != 1 and min_dist[nod - 1] > min_dist[nod] + 1) {
            min_dist[nod - 1] = min_dist[nod] + 1;
            q.push(nod - 1);
        }

        if (min_dist[a[nod]] > min_dist[nod] + 1) {
            min_dist[a[nod]] = min_dist[nod] + 1;
            q.push(a[nod]);            
        }
    }

    for (int i = 1; i <= n; i += 1) {
        cout << min_dist[i] << ' ';
    }
    return 0;
}
