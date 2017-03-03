#include <iostream>
using namespace std;

int main() {
    srand(time(NULL));
//    int mod = 1e9+7;
    int mod = 32381;
//    int n = 1e5;
    int n = mod - 1;
    cout << mod << ' ' << n << '\n';
    int start = rand() % mod;
    int r = rand() % mod;
    for (int i = 0; i + 1 < n; i += 1) {
        cout << start << ' ';
        start += r;
        start %= mod;
    }
    cout << -1 << '\n';
}
