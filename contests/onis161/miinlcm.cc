#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define int64 long long

const int kMaxVal = 1e5+5, inf = 0x3f3f3f3f;
int ap[kMaxVal];

ifstream fin("minlcm.in");
ofstream fout("minlcm.out");

int main() {
    int t; fin >> t;
    while (t--) {
        int n; fin >> n;
        vector<int> el;
        el.resize(n);
        for (int i = 0; i < n; i += 1) {
            int x; fin >> x; 
            el[i] = x;
            ap[x] += 1;
        }

        sort(el.begin(), el.end());

        int64 mn = 1ll * inf * inf;
        vector<int> min_els;
        for (int i = 1; i <= kMaxVal; i += 1) {
            min_els.clear();

            if (kMaxVal / i < int(el.size())) {
                for (int v = i; v <= kMaxVal; v += i) {
                    for (int p = 0; p < ap[v] and min_els.size() < 2; p += 1) {
                        min_els.push_back(v);
                    }
                }
            } else {
                for (auto itr : el) {
                    if (min_els.size() == 2) {
                        break;
                    }

                    if (itr % i == 0) {
                        min_els.push_back(itr);
                    }
                }
            }

            if (min_els.size() == 2) {
                mn = min(mn, 1LL * min_els[0] / i * min_els[1]);
            }
        }
        fout << mn << '\n';
        for (auto itr : el) {
            ap[itr] -= 1;
        }
        el.clear();
    }
    return 0;
}
