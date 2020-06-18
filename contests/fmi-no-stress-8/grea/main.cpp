#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 3e5;

string txt[2];
int go_right[2][kMaxN];

int main() {
    ifstream cin("grea.in");
    ofstream cout("grea.out");
    int n, k; cin >> n >> k;
    cin >> txt[0] >> txt[1];

    for (int l = 0; l < 2; l += 1) {
        int last = -1;
        for (int c = 0; c < n; c += 1) {
            if (txt[l][c] == '0') {
                last = c;
            }

            go_right[l][c] = last;
        }
    }

    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    int  cols[2] = {0, -1};
    for (int move = 1; ; move += 1) {
        int next_cols[2] = {-1, -1};
        for (int line = 0; line < 2; line += 1) {
            if (cols[line] == -1) {
                continue;
            }

            if (txt[line][cols[line] + 1] == '0') {
                next_cols[line] = max(next_cols[line], cols[line] + 1);        
            }

            next_cols[line ^ 1] = max(next_cols[line ^ 1], go_right[line ^ 1][min(n - 1, cols[line] + k)]);
        }

        if (cols[0] == next_cols[0] and cols[1] == next_cols[1]) {
            cout << -1 << '\n';
            return 0;
        }

        cols[0] = next_cols[0];
        cols[1] = next_cols[1];

        if (cols[0] == n - 1 or cols[1] == n - 1) {
            cout << move << '\n';
            return 0;
        }
    }
}
