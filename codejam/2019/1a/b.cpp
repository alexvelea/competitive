#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int numbers[6] = {17, 16, 13, 11, 9, 7};

int main() {
    int t; cin >> t;
    int __, _; cin >> __ >> _;
    for (int T = 1; T <= t; T += 1) {
        vector<int> modulo_ans = {};
        for (int i = 0; i < 6; i += 1) {
            for (int j = 0; j < 18; j += 1) {
                cout << numbers[i] << ' ';
            }
            cout << endl;

            int sum = 0;
            for (int j = 0; j < 18; j += 1) {
                int x;
                cin >> x;
                sum += x;
            }

            sum %= numbers[i];
            modulo_ans.push_back(sum);
        }

        for (int i = 1; i <= 1e6; i += 1) {
            bool ok = true;
            for (int j = 0; j < 6; j += 1) {
                if (i % numbers[j] != modulo_ans[j]) {
                    ok = false;
                }
            }

            if (ok) {
                cout << i << endl;
                int x; cin >> x;
            }

        }
    }
    return 0;
}
