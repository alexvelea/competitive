#include <iostream>
using namespace std;
int main() {
    int n = 1000, q = 10000;
    cout << n << ' ' << n << ' ' << q << '\n';
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            cout << abs(rand()) << ' ';
        }
    }

    for (int i = 1; i <= q; i += 1) {
        int l1 = rand() % (n - 1), l2 = rand() % (n - 1);
        if (l1 > l2) {
            swap(l1, l2);
        }
        l1 += 1;
        l2 += 2;
        int h = min(n - l2 + 1, l2 - l1 + 1);
        cout << l1 << ' ' << 1 << ' ' << l2 << ' ' << 1 << ' ' << h << ' ' << n << '\n';
    }
}
