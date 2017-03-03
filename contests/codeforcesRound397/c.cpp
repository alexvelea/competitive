#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5;

void Ans(int a) {
    cout << a << '\n';
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    int k, a, b; cin >> k >> a >> b;
    int num_a = a / k;
    int num_b = b / k;
    if (a % k == 0 and a) {
        Ans(num_a + num_b);
    }

    if (b % k == 0 and b) {
        Ans(num_b + num_a);
    }

    if (num_a and num_b) {
        Ans(num_a + num_b);
    }

    Ans(-1);
    return 0;
}
