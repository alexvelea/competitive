#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

typedef __int128_t int128;

struct Frac {
    int128 a, b;

    bool operator==(const Frac& rhs) const {
        return a * rhs.b == b * rhs.a;
    }

    bool operator<(const Frac& rhs) const {
        return a * rhs.b < b * rhs.a;
    }
};

int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; T += 1) {

        int n; cin >> n;
        vector<pair<int, int>> points;
        for (int i = 0; i < n; i += 1) {
            int a, b; cin >> a >> b;
            points.push_back({a, b});
        }

        Frac mn, mx;
        mn = {0, 1};
        mx = {1, 0};

        bool ok = true;
        for (int i = 0; i + 1 < n; i += 1) {
            if (points[i].first < points[i + 1].first && 
                    points[i].second < points[i + 1].second) {
                continue;
            }

            if (points[i].first == points[i + 1].first) {
                if (points[i].second > points[i + 1].second) {
                    ok = false;
                }
            } else if (points[i].second == points[i + 1].second) {
                if (points[i].first > points[i + 1].first) {
                    ok = false;
                }
            } else {
                int a = points[i].first - points[i + 1].first;
                int b = points[i].second - points[i + 1].second;
                assert(a != 0);
                assert(b != 0);

                Frac now = {abs(b), abs(a)};
                if (a > 0) {
                    mx = min(mx, now);
                } else {
                    mn = max(mn, now);
                }
            }
        }

        if (mx < mn || mx == mn) {
            ok = false;
        }

        cerr << "mn:\t" << (int)mn.a << '\t' << (int)mn.b << '\n';
        cerr << "mx:\t" << (int)mx.a << '\t' << (int)mx.b << '\n';

        if (ok == false) {
            cout << "Case #" << T << ": IMPOSSIBLE\n";
            continue;
        }

        int x = -1, y = -1;

        auto Try = [&](int a, int b) {
            Frac now = {a, b};
            if (mn < now and now < mx) {
                x = a;
                y = b;
                ok = false;
            }
        };

        for (int x = 1; ok && x <= 200; x += 1) {
            for (int y = 1; ok && y <= 200; y += 1) {
                Try(x, y);
            }
        }
/*        
            int128 y;
            if (mn.a != 0) {
                y = x * mn.b / mn.a;
            } else {
                y = 1;
            }

            if (ok) Try(x, y - 1);
            if (ok) Try(x, y + 0);
            if (ok) Try(x, y + 1);
        }
*/
        if (x == -1) {
            cout << "Case #" << T << ": IMPOSSIBLE\n";
            continue;           
        }
        cout << "Case #" << T << ": " << x << ' ' << y << '\n';
    }

    return 0;
}
