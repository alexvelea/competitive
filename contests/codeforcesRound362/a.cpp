#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

int64 lca(int64 a, int64 b) {
    while (a != b) {
        if (a < b) {
            swap(a, b);
        }

        a /= 2;
    }

    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    int q; cin >> q;
    map<pair<int64, int64>, int64> road;
    for (int i = 0; i < q; i += 1) {
        int t; cin >> t;
        if (t == 1) {
            int64 a, b, c; cin >> a >> b >> c;
            int64 l = lca(a, b);
            while (a != l) {
                int64 new_a = a / 2;
                road[{new_a, a}] += c;
                a = new_a;
            } 
            while (b != l) {
                int64 new_b = b / 2;
                road[{new_b, b}] += c;
                b = new_b;
            } 
        } else {
            int64 a, b; cin >> a >> b;
            int64 l = lca(a, b);
            int64 r = 0;
            while (a != l) {
                int64 new_a = a / 2;
                r +=road[{new_a, a}];
                a = new_a;
            } 
            while (b != l) {
                int64 new_b = b / 2;
                r += road[{new_b, b}];
                b = new_b;
            }
            cout << r << '\n';
        }
    }
    return 0;
}
