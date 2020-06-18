#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

string answer[6][30];

int els[6][6];

void Back(int line, int n) {
    if (line == n) {
        int sum = 0;
        for (int i = 0; i < n; i += 1) {
            sum += els[i][i];
        }

        string s = "";
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                s += char(els[i][j] + '0');
                s += ' ';
            }
            s.pop_back();
            s += "\n";
        }

        answer[n][sum] = s;
        return;
    }

    vector<int> perm = {};
    for (int i = 1; i <= n; i += 1) {
        perm.push_back(i);
    }

    do {
        bool ok = true;
        for (int col = 0; col < n; col += 1) {
            els[line][col] = perm[col];
        }
        for (int col = 0; col < n; col += 1) {
            for (int l = 0; l < line; l += 1) {
                if (els[l][col] == els[line][col]) {
                    ok = false;
                }
            }
        }

        if (ok) {
            Back(line + 1, n);
        }
    } while (next_permutation(perm.begin(), perm.end()));
}

void Init() {
    for (int i = 1; i <= 5; i += 1) {
        Back(0, i);
    }
}

int main() {
    int T; cin >> T;
    Init();

    for (int t = 1; t <= T; t += 1) {
        int n, k; cin >> n >> k;
        bool ok = answer[n][k].size();

        cout << "Case #" << t << ": ";
        if (ok) {
            cout << "POSSIBLE\n" << answer[n][k];
        } else {
            cout << "IMPOSSIBLE\n";
        }

    }
}
