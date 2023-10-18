#include "debug.hpp"

using namespace std;

int main() {
//    int w, l; cin >> w >> l;
    int t; cin >> t;
    int n; cin >> n;
    int team_size; cin >> team_size;

    vector<int> elo(n, 1000);

    auto match = [&](vector<int> a, vector<int> b) {
        vector<int> e = elo;

        int s = 0;
        for (auto itr : a)
            s += e[itr];
        for (auto itr : b)
            s -= e[itr];

        for (auto itr : a) {
            auto oth = -s +e[itr];

            Debug("a", itr, e[itr], oth);
            double chx = 1.0 / (1.0 + pow(10.0, double(oth - e[itr]) / 400.0));

            elo[itr] = double(elo[itr]) + 32.0 * (1.0 - chx);
        }

        for (auto itr : b) {
            auto oth = s +e[itr];

            Debug("b", itr, e[itr], oth);
            double chx = 1.0 / (1.0 + pow(10.0, double(e[itr] - oth) / 400.0));

            elo[itr] = double(elo[itr]) - 32.0 * (1.0 - chx);
        }
    };

    for (int i = 0; i < t; i += 1) {
        int s1 = 0, s2 = 0;
        vector<int> p1, p2;
        for (int i = 0; i < team_size; i += 1) {
            int p; cin >> p;
            int s; cin >> s;
            s1 += s;
            p1.push_back(p);
        }
        for (int i = 0; i < team_size; i += 1) {
            int p; cin >> p;
            int s; cin >> s;
            s2 += s;
            p2.push_back(p);
        }

        if (s1 == s2) {
            cerr << "OENIA\n";
        }
        if (s1 > s2) {
            match(p1, p2);
        } else {
            match(p2, p1);
        }
//        for (int j = 0; j < 2; j +=1 ) {
//            int p, s;
//            cin >> p >> s;
//            best[p] = max(best[p], s);
//        }
    }

    Debug(elo);
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
        if (elo[a] == elo[b]) {
            return a < b;
        }
        return elo[a] > elo[b];
    });

    for (int i = 0; i < n; i += 1) {
        cout << order[i] << ' ' << elo[order[i]] << '\n';
    }
}