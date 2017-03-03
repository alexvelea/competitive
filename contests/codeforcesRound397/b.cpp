#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    int mx = -1;
    string x; cin >> x;
    for (char itr : x) {
        int c = itr - 'a';
        if (c > mx + 1) {
            cout << "NO\n";
            exit(0);
        }

        mx = max(mx, c);
    }
    cout << "YES\n";
    return 0;
}
