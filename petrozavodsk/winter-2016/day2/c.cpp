#include <iostream>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <ctime>
using namespace std;

const int kMaxN = 1e5+5, kMod = 1e9+7;
//const int kMaxN = 55, kMod = 2;

typedef long long int64;

#define Debug(...) fprintf(stderr, __VA_ARGS__)

int& Mod(int& a) {
//	return a &= 1;
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

struct Helper {
    int e[14];
    int c[14];

    Helper(int64 x)  {
        for (int i = 0; i < 14; i += 1) {
            c[i] = 0;
        }
        for (int i = 0; i < 13; i += 1) {
            e[i] = x % 14;
            c[e[i]] += 1;
            x /= 14;
        }
        e[13] = 0;
    }

    int64 ToInt() {
        int64 r = 0;
        for (int i = 12; i >= 0; i -= 1) {
            r *= 14;
            r += e[i];
        }
        return r;
    }

    Helper(const vector<int>& _) {
        for (int i = 0; i < 14; i += 1) {
            c[i] = 0;
            e[i] = 0;
        }
        for (int i = 0; i < (int)_.size(); i += 1) {
            e[i] = _[i];
            c[e[i]]++;
        }
    }

    void Normalize() {
        static int perm[16];
        memset(perm, 0, 16 * 4);
        perm[0] = -1;
        int next = 0;
        for (auto itr : e) {
            if (perm[itr] == 0) {
                perm[itr] = ++next;
            }
        }
        perm[0] = 0;

        for (auto& itr : e) {
            c[itr]--;
            c[perm[itr]]++;
            itr = perm[itr];
        }
    }

    void GoLeft() {
        for (int i = 0; i + 1 < 14; i += 1) {
            e[i] = e[i + 1];
        }
    }

    void debug() {
        for (int i = 0; i < 13; i += 1) {
            Debug("%d\t", e[i]);
        }
        Debug("\n");
    }
};

unordered_map<int64, int> result;

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
        unordered_map<int64, int> next_map;
        for (auto itr : result) {
            int num = itr.second;
            Helper not_taken(itr.first);
            Helper taken(itr.first);

            not_taken.e[13] = 0;
            not_taken.c[0]++;

            vector<int> fill(20, 0);
            int bonus = 13 - node;
            for (auto child : vertex[node]) {
                if (taken.e[child + bonus]) {
                    fill[taken.e[child + bonus]] = true;
                }
            }

            taken.c[13] = 1;
            taken.e[13] = 13;
            for (auto& c : taken.e) {
                if (fill[c]) {
                    taken.c[c] -= 1;
                    c = 13;
                    taken.c[13] += 1;
                }
            }

            taken.Normalize();

            auto Check = [&](Helper&& conf) {
                 if (conf.e[0] and conf.c[conf.e[0]] == 1) {
                    if (conf.c[0] == 13) {
                        Mod(answer += num);
                    }
                    return;
                }
                conf.GoLeft();
                conf.Normalize();
                next_map[conf.ToInt()] += num;               
            };

            Check(move(taken));
            Check(move(not_taken));
        }
        vector<int> v(12, 0);
        Helper h(0);
        h.e[12] = 1;
        next_map[h.ToInt()] = 1;
        result = next_map;
        mx = max(mx, (int)result.size());
    }
/*
        for (auto itr : result) {
            Helper h(itr.first);
            Debug("[%d]\t", itr.second);
            h.debug();
        }
*/
    for (auto itr : result) {
        Helper conf = itr.first;
        int num = itr.second;
        if (conf.c[1] and conf.c[2] == 0) {
            Mod(answer += num);
        }
    }

    cout << answer << '\n';
}
