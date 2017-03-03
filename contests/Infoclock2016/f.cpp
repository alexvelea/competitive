#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int k; cin >> k;
    if (k == 0) {
        cout << "+\n";
        return 0;
    }

    vector<vector<int>> els = {{+1, -1}, {+1, +1}};

    for (int i = 2; i <= k; i += 1) {
        auto p = els;
        vector<vector<int>> P;
        int n = els.size();
        for (int i = 0; i < n; i += 1) {
            vector<int> l = p[i];
            for (auto itr : els[i]) {
                l.push_back(itr);
            }
            P.push_back(l);
        }

         for (int i = 0; i < n; i += 1) {
            vector<int> l = p[i];
            for (auto& itr : l) {
                itr *= -1;
            }
            for (auto itr : els[i]) {
                l.push_back(itr);
            }
            P.push_back(l);
        }

         els = P;
    }

    for (auto itr : els) {
        for (auto itr2 : itr) {
            if (itr2 == +1) {
                cout << "+";
            } else {
                cout << "*";
            }   
        }
        cout << '\n';
    }
}

