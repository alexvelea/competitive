#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int el[4][4];

int dx[8] = {0, +1, +1, +1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, +1, +1, +1, 0, -1};

bool Solve(int player) {
    for (int i = 0; i < 4; i += 1) {
        for (int j = 0; j < 4; j += 1) {
            for (int d = 0; d < 8; d += 1) {
                int x = i, y = j;
                bool ok = true;
                for (int l = 0; l < 3; l += 1) {
                    if (!(0 <= x and x < 4 and 0 <= y and y < 4)) {
                        ok = false;
                        break;
                    }

                    if (el[x][y] != player) {
                        ok = false;
                        break;
                    }

                    x += dx[d];
                    y += dy[d];
                }

                if (ok) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    int num1 = 0, num2 = 0;
    for (int i = 0; i < 4; i += 1) {
        for (int j = 0; j < 4; j += 1) {
            char c; cin >> c;
            if (c == '.') {
                el[i][j] = 0;
            } else if (c == 'x') {
                el[i][j] = 1;
                num1 += 1;
            } else if (c == 'o') {
                el[i][j] = 2;
                num2 += 1;
            }
        }
    }

    int player = 0;
    if (num1 == num2) {
        player = 1;
    } else {
        player = 2;
    }

    bool ok = false;
    for (int i = 0; i < 4; i += 1) {
        for (int j = 0; j < 4; j += 1) {
            if (el[i][j] == 0) {
                el[i][j] = player;
                ok |= Solve(player);
                el[i][j] = 0;
            }
        }
    }

    if (ok) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}

