#include <iostream>
using namespace std;

#define int64 long long

int main() {
    ios_base::sync_with_stdio(false);
    int64 a, b, c; cin >> a >> b >> c;
    if (c == 0) {
        cout << (a == b ? ("YES\n") : ("NO\n"));
        return 0;
    }

    int64 index = (b - a) / c;
    if (index * c + a == b and index >= 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
