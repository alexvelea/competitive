#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    int h = 0;
    int mx = 20000;
    bool ok = true;
    for (int i = 0; i < n; i += 1) {
        int x; cin >> x;
        string dir; cin >> dir;
        if (dir == "East" or dir == "West") {
            if (h == 0 or h == mx) {
                ok = false;
            }
            continue;
        }
        if (dir == "North") {
            h -= x;
            if (h  < 0) {
                ok = false;
            }
        } else {
            h += x;
            if (h > mx) {
                ok = false;
            }
        }
    }

    if (h != 0) {
        ok = false;
    }

    if (ok) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
