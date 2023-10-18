#include "debug.hpp"

using namespace std;

int main() {
    int t; cin >> t;
    int n; cin >> n;

    vector<int> num_wins(n);
    for (int i = 0; i < t; i += 1) {
        int p1, s1, p2, s2;
        cin >> p1 >> s1 >> p2 >> s2;
        if (s1 > s2) {
            num_wins[p1] += 1;
        } else {
            num_wins[p2] += 1;
        }
//        for (int j = 0; j < 2; j +=1 ) {
//            int p, s;
//            cin >> p >> s;
//            best[p] = max(best[p], s);
//        }
    }

//    int mx = 0;
//    for (auto& itr : best) {
//        mx = max(mx, itr);
//    }
//
//    for (int i = 0; i < n; i += 1) {
//        if (best[i] == mx) {
//            cout << i << ' ' << best[i] << '\n';
//            return 0;
//        }
//    }

    vector<int> order;
    for (int i = 0; i < n; i += 1) {
        order.push_back(i);
    }

    sort(order.begin(), order.end(), [&](auto a, auto b) {
        if (num_wins[a] == num_wins[b]) {
            return a < b;
        }
        return num_wins[a] > num_wins[b];
    });

    for (int i = 0; i < n; i += 1) {
        cout << order[i] << ' ' << num_wins[order[i]] << '\n';
    }
}