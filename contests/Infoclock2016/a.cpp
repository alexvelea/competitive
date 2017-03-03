#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m; cin >> m >> n;
    vector<int> ok(n, false);
    while (m--) {
        int x; cin >> x;
        while (x--) {
            int y; cin >> y;
            y--;
            ok[y] = true;
        }
    }

    bool k = true;
    for (auto itr : ok) {
        k&= itr;
    }


    if (k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}

