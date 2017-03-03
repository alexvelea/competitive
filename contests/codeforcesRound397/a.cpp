#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    string home; cin >> home;
    int num_home = 0;
    for (int i = 0; i < n; i += 1) {
        string txt; cin >> txt;
        if (txt.substr(0, 3) == home) {
            num_home += 1;
        }
    }

    if (num_home * 2 == n) {
        cout << "home\n";
    } else {
        cout << "contest\n";
    }
    return 0;
}
