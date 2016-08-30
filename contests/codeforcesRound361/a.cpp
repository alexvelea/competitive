#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;

int d[4][10];

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    string txt; cin >> txt;
    d[0][1] = d[0][4] = d[0][7] = d[0][0] = 1;
    d[1][3] = d[1][6] = d[1][9] = d[1][0] = 1;
    d[2][1] = d[2][2] = d[2][3] = 1;
    d[3][7] = d[3][0] = d[3][9] = 1;

    bool ans = false;
    for (int j = 0; j < 4; j += 1) {
        bool ok = false;
        for (int i = 0; i < n; i += 1) {
            ok |= d[j][txt[i] - '0'];
        }
        ans |= !ok;
    }

    if (ans == true) {
        cout << "NO\n"; 
    } else {
        cout << "YES\n";
    }
    return 0;
}
