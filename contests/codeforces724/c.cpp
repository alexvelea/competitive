#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
const int inf = 0x3f3f3f3f;

int n, m, p, g, ng2, n2, m2;

int64 Time(int64 x, int64 y) {
    if (x == y) {
        return x;
    }

    if (n == m) {
        return 1e18;
    }
    
    // 2 * n * a + x == 2 * m * b + y
    // a = (2 * m * b + y - x) / (2 * n)
    
    int b;

    if (g == 2 * n) {
        if ((y - x + 2 * n) % (2 * n) != 0) {
            return 1e18;
        }

        if (y < x) {
            b = 1;
        } else {
            b = 0;
        }
    } else {
        int z;
        if (y - x < 0) {
            z = y - x + (n2);
        } else {
            z = y - x;
        }

    //    printf("x:%ld\ty:%ld\n", x, y);
    //    printf("g:%d\tz:%d\n", g, z);

        if (__gcd(g, z) != g) {
            return 1e18;
        }

        int r = (n2 - z) % (n2);
        b = (1LL * (r / g) * p) % (ng2);
    }
//    printf("r:%d\tb:%d\n", r, b);
    int64 a = (1LL * (m2 * b + y - x) / (n2));
//    printf("a:%d\n\n", a);
    return 1LL * n2 * a + x;
}

void Init() {
    g = __gcd(2 * m, 2 * n);
    
    ng2 = 2 * n / g;
    n2 = 2 * n;
    m2 = 2 * m;

    p = 1;
    int sum = (2 * m) % (n2);
    
    if (n == m) { 
        p = 0;
        return;
    }
    
    if (g == 2 * n) {
        return;
    }

    while (sum != g) {
        sum += 2 * m;
        sum %= 2 * n;
        p += 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int k; cin >> n >> m >> k;

    Init();

    int64 mx_time = min(min(Time(0, m), Time(n, m)), Time(n, 0));
    for (int i = 0; i < k; i += 1) {
        int x, y; cin >> x >> y;
        int64 t = min(min(min(Time(x, y), Time(2 * n - x, y)), Time(x, 2 * m - y)), Time(2 * n - x, 2 * m - y));
        if (t < mx_time) {
            cout << t << '\n';
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}
