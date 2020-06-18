#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct SpecialInt {
    int base_number;
    int initial_v;
    int num_2, num_3;

    SpecialInt(int v) : num_2(0), num_3(0) {
        initial_v = v;
        while (v % 2 == 0) {
            v /= 2;
            num_2 += 1;
        }

        while (v % 3 == 0) {
            v /= 3;
            num_3 += 1;
        }

        base_number = v;
    }

    bool operator<(const SpecialInt& rhs) const {
        return make_pair(-num_2, num_3) < make_pair(-rhs.num_2, rhs.num_3);
    }

    bool IsLower (const SpecialInt& rhs) const {
        return num_2 >= rhs.num_2 and num_3 <= rhs.num_3 and base_number == rhs.base_number;
    }
};

int main() {
    ifstream cin("calorifer.in");
    ofstream cout("calorifer.out");

    vector<SpecialInt> els;

    int n; cin >> n;
    
    for (int i = 0; i < n; i += 1) {
        int x; cin >> x;
        els.push_back(x);
    }

    sort(els.begin(), els.end());
    bool ok = true;
    
    for (int i = 1; i < n; i += 1) {
        ok &= els[i - 1].IsLower(els[i]);
//        ok &= (els[i - 1].initial_v != els[i].initial_v);
    }

    if (not ok) {
        cout << -1 << '\n';
        return 0;
    }
    
    for (auto& itr : els) {
        cout << itr.initial_v << ' ';
    }
    cout << '\n';
}
