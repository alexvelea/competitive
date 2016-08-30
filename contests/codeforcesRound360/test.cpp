#include <iostream>
using namespace std;
int main() {
    int n = 1000, m = n * (n - 1) / 2, q = 1000;
    cout << n << ' ' << m << ' ' << q << '\n';
    for (int i = 1; i <= n; i += 1) {
        for (int j = i + 1; j <= n; j += 1) {
            cout << i << ' ' << j << ' ' << rand() << '\n'; 
        }
    }
    for (int i = 0; i < q; i += 1) {
        int a = rand() % m + 1;
        int b = rand() % m + 1;
        if ( a > b) {
        swap(a, b);}

        cout << a << ' ' << b << '\n';
    }
    return 0;
}
