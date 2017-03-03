#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    int sum = 0;
    int pos = -1;
    for (int i = 0; i < n; i += 1) {
        int x; cin >> x;
        sum += x;
        if (sum != 0) {
            pos = i;
        }
    }
    if (sum == 0) {
        if (pos == -1) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            cout << "2\n" << 1 << ' ' << pos + 1 << '\n' << pos + 2 << ' ' << n << '\n';
        }
    } else {
        cout << "YES\n1\n1 " << n << '\n';
    }
    return 0;
}

