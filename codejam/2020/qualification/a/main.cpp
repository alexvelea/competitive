#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 105;
int els[kMaxN][kMaxN];

vector<int> lines[100], cols[100];

bool NotUnique(vector<int> els) {
    sort(els.begin(), els.end());
    return unique(els.begin(), els.end()) != els.end();
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        int n; cin >> n;

        int sum = 0;
        for (int i = 1; i <= n; i += 1) {
            lines[i].clear();
            cols[i].clear();
        }

        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= n; j += 1) {
                int x; cin >> x;
                lines[i].push_back(x);
                cols[j].push_back(x);
                if (i == j) { sum += x; }
            }
        }

        int num_lines = 0, num_cols = 0;
        for (int i = 1; i <= n; i += 1) {
            num_lines += NotUnique(lines[i]);
            num_cols += NotUnique(cols[i]);
        }
        
        cout << "Case #" << t << ": ";
        cout << sum << ' ' << num_lines << ' ' << num_cols << '\n';

    }
}
