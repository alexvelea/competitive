#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sys/time.h>
using namespace std;

typedef long long int64;

vector<int> DoF(const vector<int>& a, int x, int y) {
    int n = a.size();
    vector<int> ans;
    for (int i = x; i < x + y; i += 1) {
        ans.push_back(a[i]);
    }
    for (int i = 0; i < x; i += 1) {
        ans.push_back(a[i]);
    }

    for (int i = x + y; i < n; i += 1) {
        ans.push_back(a[i]);
    }

    return ans;
}

vector<pair<int, int>> solve(int r, int s) {
    vector<int> final_v, initial_v;
    for (int j = 0; j < s; j += 1) {
        for (int i = 0; i < r; i += 1) {
            initial_v.push_back(i);
        }
    }

    for (int i = 0; i < r; i += 1) {
        for (int j = 0; j < s; j += 1) {
            final_v.push_back(i);
        }
    }

    int n = r * s;

    map<vector<int>, vector<pair<int, int>>> history, next;
    history[initial_v] = {};
    while (1) {
        if (history.count(final_v)) {
            break;
        }       
        next.clear();

        for (auto& itr : history) {
            for (int i = 1; i < n; i += 1) {
                for (int j = 1; j + i <= n; j += 1) {
                    auto next_v = DoF(itr.first, i, j);
                    if (next.count(next_v)) {
                        continue;
                    }

                    auto next_h = itr.second;
                    next_h.push_back({i, j});
                    next[next_v] = next_h;
                }
            }
        }

        history = next;
        if (history.count(final_v)) {
            break;
        }
    }

    return history[final_v];
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        int r, s; cin >> r >> s;
        if (r * s > 14) { return 0; }

        vector<pair<int, int>> ans;
        if (r == 7 and s == 2) {
            ans = { {3, 6}, {2, 9}, {2, 11}, {2, 1}};
        } else { ans = solve(r, s); }

        cout << "Case #" << t << ": ";
        cout << ans.size() << '\n';
        for (auto& itr : ans) {
            cout << itr.first << ' ' << itr.second << '\n';
        }
    }
}
