#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;  
    int x = 0;
    for (int i = 0; i < n; i += 1) {
        int p; cin >> p;
        x += 1 - p;
    }

    if ((x == 1 and n != 1)  or (x == 0 and n == 1)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
