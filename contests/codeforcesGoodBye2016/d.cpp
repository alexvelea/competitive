#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

const int kMaxN = 400;

bool viz[kMaxN][kMaxN];
int dx[8] = {+1, +1, 0, -1, -1, -1, 0, +1};
int dy[8] = {0, +1, +1, +1, 0, -1, -1, -1};
bool has_firework[kMaxN][kMaxN][8];
bool next_has_firework[kMaxN][kMaxN][8];

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    has_firework[200][200][0] = true;

    for (int i = 0; i < n; i += 1) {
        int t; cin >> t;
        for (int x = 0; x < kMaxN; x += 1) {
            for (int y = 0; y < kMaxN; y += 1) {
                for (int d = 0; d < 8; d += 1) {
                    if (not has_firework[x][y][d]) {
                        continue;
                    }

                    int nx = x;
                    int ny = y;
                    for (int i = 0; i < t; i += 1) {
                        nx += dx[d];
                        ny += dy[d];
                        viz[nx][ny] = true;
                    }
                    next_has_firework[nx][ny][(d + 1) % 8] = true;
                    next_has_firework[nx][ny][(d + 7) % 8] = true;
                }
            }
        }

        for (int i = 0; i < kMaxN; i += 1) {
            for (int j = 0; j < kMaxN; j += 1) {
                for (int d = 0; d < 8; d += 1) {
                    has_firework[i][j][d] = next_has_firework[i][j][d];
                    next_has_firework[i][j][d] = false;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < kMaxN; i += 1) {
        for (int j = 0; j < kMaxN; j += 1) {
            ans += viz[i][j];   
        }
    }

    cout << ans << '\n';
    
    return 0;
}
