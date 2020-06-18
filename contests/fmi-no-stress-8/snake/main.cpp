#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int kMaxN = 100;

int h, w;
int els[kMaxN][kMaxN];
int taken[kMaxN * kMaxN + 5];

int dx[4] = {+0, +0, -1, +1};
int dy[4] = {-1, +1, +0, +0};

bool force_take = false;

void Fill(int x, int y) {
    if (els[x][y] != 0) {
        return;
    }

    vector<int> possible;

    for (int d1 = 0; d1 < 4; d1 += 1) {
        if (0 <= x + dx[d1] and x + dx[d1] < h and 0 <= y + dy[d1] and y + dy[d1] < w) { } else { continue; }
        int a = els[x + dx[d1]][y + dy[d1]];
        if (a > 0 and a % 2 == 1) {
            int d = d1;
            for (int d1 = d + 1; d1 < 4; d1 += 1) {
                if (0 <= x + dx[d1] and x + dx[d1] < h and 0 <= y + dy[d1] and y + dy[d1] < w) { } else { continue; }
                int b = els[x + dx[d1]][y + dy[d1]];

                if (abs(a - b) != 2) continue;

                int mid = (a + b) / 2;
                if (taken[mid]) { continue; }
                
                possible.push_back(mid);
            }
        }
    }

    if (possible.size() != 1 and force_take == false) {
        return;
    }

    if (possible.size() == 0) {
        return;
    }

    force_take = false;

    els[x][y] = possible[0];
    taken[possible[0]] = true;

    Fill(x + 1, y + 1);
    Fill(x + 1, y - 1);
    Fill(x - 1, y + 1);
    Fill(x - 1, y - 1);
}

int main() {
    ifstream cin("snake.in");
    ofstream cout("snake.out");
    cin >> h >> w;
    int n; cin >> n;

    for (int i = 0; i < h; i += 1)
        for (int j = 0; j < w; j += 1) {
            cin >> els[i][j];
        }

    for (int i = 1; i <= n; i += 2) {
        taken[i] = true;
    }

    while (1) {
        for (int i = 0; i < h; i += 1)
            for (int j = 0; j < w; j += 1) {
                Fill(i, j);
            }

        force_take = true;

        bool k  = true;
        for (int i = 1; i <= n; i += 1) {
            if (not taken[i]) {
                k = false;
            }
        }

        if (k) { break; }
    }

    for (int i = 0; i < h; i += 1) {
        for (int j = 0; j < w; j += 1) {
            cout << els[i][j] << ' ';
        }
        cout << '\n';
    }

}
