//Problem b @ 22-07-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

void solve(string &a, int n) {
    for (int i = 0; i < int(a.size()); i += 2 * n) {
        for (int j = 0; j < n; ++j) {
            if (a[i + j] != a[i + n + j]) {
                if (a[i + j] > a[i + n + j]) {
                    for (int l = 0; l < n; ++l) {
                        swap(a[i + l], a[i + n + l]);
                    }
                }
                break;
            }
        }
    }
    return ;
}          

int main() {
	ios::sync_with_stdio(false);
    string a, b;
    cin >> a >> b;
	int l = 0, n = a.size();
    while (n != 1 and n % 2 == 0) {
        l++;
        n /= 2;
    }
    while (l--) {
        solve(a, n);
        solve(b, n);
        n *= 2;
    }
    if (a != b) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }

    return 0;
}
