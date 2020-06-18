#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

int main() {
//    ifstream cin("lautari.in");
//    ofstream cout("lautari.out");
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> els(n);
    for (int i = 0; i < n; i += 1) {
        cin >> els[i];
    }

    int itr_l = 0, itr_r = 0;
    map<int, int> cnt_l, cnt_r;

    long long ans = 0;
    for (int i = 0; i < n; i += 1) {
        auto Add = [&](map<int, int>& m, int v) {
            m[v] += 1;
        };

        auto Del = [&](map<int, int>& m, int v) {
            m[v] -= 1;
            if (m[v] == 0) {
                m.erase(v);
            }
        };

        // expand left until we first reach l in interval [i, itr_l)
        while (itr_l < n and (int)cnt_l.size() < l) {
            Add(cnt_l, els[itr_l]);
            itr_l += 1;
        }

        while (itr_r < n and (int)cnt_r.size() <= r) {
            Add(cnt_r, els[itr_r]);
            itr_r += 1;
        }

        if ((int)cnt_l.size() < l) {
            break;
        }

        ans += itr_r - itr_l + 1 - ((int)cnt_r.size() == r + 1);

        cerr << itr_l << '\t' << itr_r << '\n';

        Del(cnt_l, els[i]);
        Del(cnt_r, els[i]);
    }

    cout << ans << '\n';
}
