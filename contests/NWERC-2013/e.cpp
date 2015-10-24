//Problem e @ 03-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 10000;

#define int64 long long

int64 tower[kMaxN * 15];

vector<pair<int, int> > desc(int el) {
    vector<pair<int, int> > rez;
    for (int d = 2; d * d <= el; ++d) {
        if (el % d == 0) {
            int exp = 0;
            while (el % d == 0) {
                ++exp;
                el /= d;
            }
            rez.push_back(make_pair(d, exp));
        }
    }
    if (el != 1) {
        rez.push_back(make_pair(el, 1));
    }
    return rez;
}

int main() {
	ios::sync_with_stdio(false);
    vector<int> possible[kMaxN * 15];
    // compute tower(t)
    for (int d = 2; d < kMaxN * 15; ++d) {
        for (int64 v = d, p = 1; v <= kMaxN * 15; v *= d, p++) {
            possible[v].push_back(p);
        }
    }
    tower[1] = 1;
    for (int t = 2; t < kMaxN * 15; ++t) {
        int64 rez = 0;
        for (auto itr : possible[t]) {
            rez += tower[itr];
        }
        tower[t] = rez;
    }

    string txt;
    while (cin >> txt) {
        txt += '^';
        vector<int> el;
        int aux = 0;
        for (auto itr : txt) {
            if (itr == '^') {
                el.push_back(aux);
                aux = 0;
            } else {
                aux *= 10;
                aux += itr - '0';
            }
        }
        
        auto descA = desc(el[0]);
        auto descB = desc(el[1]);

        int gcd = 0;
        for (auto itr : descA) {
            gcd = __gcd(gcd, itr.second);
        }
        descA = desc(gcd);

        for (auto &itr : descB) {
            itr.second *= el[2];
        }
        for (auto itr : descA) {
            bool ok = true;
            for (auto &itr2 : descB) {
                if (itr.first == itr2.first) {
                    itr2.second += itr.second; 
                    ok = false;
                }
            }
            if (ok) {
                descB.push_back(itr);
            }
        }
        sort(descB.begin(), descB.end());
        int mx = 0;
        for (auto itr : descB) {
            mx = max(mx, itr.second);
        }
        int64 rez = 0;
        for (int t = 2; t <= mx; ++t) {
            int64 prod = 1;
            for (auto itr : descB) {
                prod *= 1LL * (int(itr.second / t) + 1);
            }
            prod--;
            prod *= 1LL * tower[t];
            rez += prod;
        }
        cout << rez << '\n';
    }
	return 0;
}
