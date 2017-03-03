#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 2e3;

vector<int> el;

void Sort() {
    sort(el.begin(), el.end());
}

int main() {
    ios_base::sync_with_stdio(false);

    int n, k, x; cin >> n >> k >> x;
    el = vector<int>(kMaxN, 0);
    for (int i = 0; i < n; i += 1) {
        int itr;
        cin >> itr;
        el[itr] ++;
    }

    for (int i = 1; i <= k; i += 1) {
        vector<int> next(kMaxN, 0);
        int num = 0;
        for (int j = 0; j < kMaxN; j += 1) {
            if (el[j] == 0) {
                continue;
            }

            int move = 0;
            if (num & 1) {
                move = el[j] / 2;
            } else {
                move = (el[j] + 1) / 2;
            }

            num += el[j];
            next[j ^ x] += move;
            next[j] += el[j] - move;
        }

        el = next;
    }

    for (int j = kMaxN - 1; j; j -= 1) {
        if (el[j]) {
            cout << j << '\n';
            break;
        }
    }

    for (int j = 0; j < kMaxN; j += 1) {
        if (el[j]) {
            cout << j << '\n';
            break;
        }
    }
    return 0;
}
