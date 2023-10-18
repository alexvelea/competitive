#include "debug.hpp"
#include <random>
using namespace std;

int main() {
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
            double chx = 1.0 / (1.0 + pow(10.0, double(oth - e[itr]) / 400.0));

            elo[itr] = double(elo[itr]) + 32.0 * (1.0 - chx);
        }
        for (auto itr : b) {
            auto oth = s +e[itr];
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

        if (s1 > s2) {
            match(p1, p2);
        } else {
            match(p2, p1);
        }
    }

//    vector<int> order;
//    for (int i = 0; i < n; i += 1) {
//        order.push_back(i);
//    }
//    for (int i = 0; i < n; i += 1) {
//        cout << order[i] << ' ' << elo[order[i]] << '\n';
//    }

    int maxElo, minScore; cin >> maxElo >> minScore;
    Debug(maxElo, minScore);
    int q; cin >> q;
    vector<int> players(q);
    for (auto& itr : players) {
        cin >> itr;
    }

    sort(players.begin(), players.end(), [&](auto a, auto b) {
        if (elo[a] == elo[b]) {
            return a < b;
        }
        return elo[a] > elo[b];
    });

    auto find = [&](vector<int> p) {
        auto best = p;
        int mn = 1e9;

        auto getScore = [&]() {
            int s = 0;
            for (int a = 0; a < team_size; a += 1) {
                s += elo[p[a]];
                s -= elo[p[a + team_size]];
            }
            return abs(s);
        };

        std::random_device rd;
        std::mt19937 g(rd());

        for (int i = 0; i < 1000; i += 1) {
            shuffle(p.begin(), p.end(), g);
            auto now = getScore();
            if (now < mn) {
                mn = now;
                best = p;
            }
        }

        return best;
    };

    int s = 0;
    for (int i = 0; i < q; i += 2 * team_size) {
        auto p = find(vector<int>(players.begin() + i, players.begin() + i + 2 * team_size));

        for (int a = 0; a < team_size; a += 1) {
            s += elo[p[a]];
            s -= elo[p[a + team_size]];
        }

        for (auto itr : p) {
            cout << itr << ' ';
        }
        cout << '\n';
    }

    if (s > minScore) {
        cerr << "PANIC\n";
    }
}