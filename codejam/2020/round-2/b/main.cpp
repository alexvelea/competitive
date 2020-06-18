#include <sys/time.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

typedef long long int64;

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        int n, m; cin >> n >> m;
        vector<int> final_time(n + 1, 0);
        vector<pair<int, int>> v_timed_nodes, v_ordered_nodes;
        for (int i = 2; i <= n; i += 1) {
            int x; cin >> x;
            if (x < 0) {
                v_ordered_nodes.push_back({-x, i});
            } else {
                final_time[i] = x;
                v_timed_nodes.push_back({x, i});
            }
        }

        sort(v_ordered_nodes.begin(), v_ordered_nodes.end());
        sort(v_timed_nodes.begin(), v_timed_nodes.end());

        queue<pair<int, int>> timed_nodes, ordered_nodes;

        for (auto itr : v_timed_nodes) { timed_nodes.push(itr); }
        for (auto itr : v_ordered_nodes) { ordered_nodes.push(itr); }

        int inside = 1;
        int last_time = 0;
        while (ordered_nodes.size() or timed_nodes.size()) {
            if (ordered_nodes.size() and ordered_nodes.front().first == inside) {
                // put all
                last_time += 1;
                int old_inside = inside;
                while (ordered_nodes.size() and ordered_nodes.front().first == old_inside) {
                    int node_id = ordered_nodes.front().second;
                    final_time[node_id] = last_time;
                    inside += 1;
                    ordered_nodes.pop();
                }
            } else {
                assert(timed_nodes.size());
                last_time = timed_nodes.front().first;
            }

            // put all timed nodes
            while (timed_nodes.size() and timed_nodes.front().first == last_time) {
                inside += 1;
                timed_nodes.pop();
            }
        }

        cout << "Case #" << t << ": ";
        for (int i = 1; i <= m; i += 1) {
            int a, b; cin >> a >> b;
            int edge = abs(final_time[a] - final_time[b]);
            if (edge == 0) { edge = 1; }
            cout << edge << ' ';
        }
        cout << '\n';
        cout.flush();
    }

    return 0;
}
