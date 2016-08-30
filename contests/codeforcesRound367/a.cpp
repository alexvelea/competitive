#include <algorithm>
#include <functional>
#include <cmath>
#include <iomanip>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int x, y; cin >> x >> y;
    int n; cin >> n;
    double mn = 1e9;
    for (int i = 1; i <= n; i += 1) {
        int a, b, v; cin >> a >> b >> v;
        double dist = sqrt(1.0 * (x - a) * (x - a) + 1.0 * (y - b) * (y - b)) * 1.0 / v;
        mn = min(mn, dist);
    }

    cout << fixed << setprecision(9) << mn << '\n'; 
    return 0;
}
