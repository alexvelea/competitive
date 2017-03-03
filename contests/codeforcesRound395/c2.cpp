#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5;

int main() {
    ios_base::sync_with_stdio(false);
    cout << "int mod, first, ratio, num" << '\n';
    int mod, first, ratio, num; cin >> mod >> first >> ratio >> num;
    vector<int> elements;
    for (int i = 0; i < num; i += 1) {
        elements.push_back(first % mod);
        first += ratio;
        first %= mod;
        sort(elements.begin(), elements.end());
        elements.push_back(elements.front() + mod);
        for (int j = 0; j <= i; j += 1) {
            cout << elements[j + 1] - elements[j] << '\t';
        }
        elements.pop_back();
        cout << '\n';
    }
    return 0;
}
