#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int kMaxN = 1e5+5, kMod = 1e9+7;
//const int kMaxN = 55, kMod = 2;

int& Mod(int& a) {
    if (a >= 2 * kMod) {
        return a %= kMod;
    } else if (a >= kMod) {
        return a -= kMod;
    } else if (a < 0) {
        return Mod(a += kMod);
    } else {
        return a;
    }
}

vector<int> vertex[kMaxN];

vector<int> Normalize(vector<int> el) {
    vector<int> perm(20, 0);
    perm[0] = -1;
    int next = 0;
    for (auto itr : el) {
        if (perm[itr] == 0) {
            perm[itr] = ++next;
        }
    }
    perm[0] = 0;

    for (auto& itr : el) {
        itr = perm[itr];
    }

    return el;
}

int Count(const vector<int>& el, int val) {
    int r = 0;
    for (auto itr : el) {
        r += (itr == val);
    }
    return r;
}

map<vector<int>, int> result;

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i += 1) {
        int a, b; cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        vertex[b].push_back(a);
    }

    int answer = 0;

    int mx = 0;
    for (int node = 1; node <= n; node += 1) {
        map<vector<int>, int> next_map;
        for (auto itr : result) {
            int num = itr.second;
            auto not_taken = itr.first;
            auto taken = itr.first;
            not_taken.push_back(0);
            vector<int> fill(20, 0);
            int bonus = (int)taken.size() - node;
            for (auto child : vertex[node]) {
                if (taken[child + bonus]) {
                    fill[taken[child + bonus]] = true;
                }
            }

            for (auto& c : taken) {
                if (fill[c]) {
                    c = 15;
                }
            }

            taken.push_back(15);
            taken = Normalize(taken);

            for (auto conf : {taken, not_taken}) {
                if (conf.size() == 14 and conf.front() and Count(conf, conf.front()) == 1) {
                    if (Count(conf, 0) == (int)conf.size() - 1) {
                        Mod(answer += num);
                    }
                    continue;
                }
                if (conf.size() == 14) {
                    conf.erase(conf.begin());
                }
                conf = Normalize(conf);
                next_map[conf] += num;
            }
        }
        vector<int> v(min(12, node - 1), 0);
        v.push_back(1);
        next_map[v] = 1;
        result = next_map;
        mx = max(mx, (int)result.size());
    }

//    cerr << mx << '\n';

    for (auto itr : result) {
        auto conf = itr.first;
        int num = itr.second;
        if (Count(conf, 1) and Count(conf, 2) == 0) {
            Mod(answer += num);
        }
    }

    cout << answer << '\n';
}
