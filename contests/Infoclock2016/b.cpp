#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

int64 Compute(int a) {
    return 1LL * a * (a + 1) / 2;
}

int main() {
    int64 n; cin >> n;
    int64 before = 0;
    int num_elements_current = 0;

    for (int p = 28; p >= 0; p -= 1) {
        if (Compute(num_elements_current + (1 << p)) < n) {
            num_elements_current += (1 << p);
        }
    }

    before = Compute(num_elements_current);
    cout << n - before << '\n';
    return 0;
}

