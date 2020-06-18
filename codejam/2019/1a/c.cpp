#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string ans[21][21];

bool RandomTry(int i, int j) {
    for (int _ = 0; _ < 1e3; _ += 1) {
        vector<vector<int>> used(i, vector<int>(j, 0));
        int start_x = rand() % i;
        int start_y = rand() % j;
        used[start_x][start_y] = true;
        string history = to_string(start_x + 1) + " " + to_string(start_y + 1) + "\n";

        bool k = true;
        for (int s = 1; s < i * j; s += 1) {
            int next_x = -1, next_y = -1;
            bool next = false;
            for (int _ = 0; _ < i * j * 50; _ += 1) {
                next_x = rand() % i;
                next_y = rand() % j;

                if (next_x == start_x or next_y == start_y or next_x - next_y == start_x - start_y or next_x + next_y == start_x + start_y) {
                    continue;
                }

                if (used[next_x][next_y]) {
                    continue;
                }

                next = true;
                break;
            }

            if (not next) {
                k = false;
                break;
            }

            used[next_x][next_y] = true;
            start_x = next_x;
            start_y = next_y;
            history += to_string(start_x + 1) + " " + to_string(start_y + 1) + "\n";
        }

        if (k) {
            ans[i][j] = history;
            return true;
        }
    }

    return false;
}

int main() {
    for (int i = 2; i <= 20; i += 1) {
        for (int j = 2; j <= 20; j += 1) {            
            RandomTry(i, j);
        }
    }

    int t; cin >> t;
    for (int T = 1; T <= t; T += 1) {
        int x, y; cin >> x >> y;
        string as = "POSSIBLE";
        if ((x == 2 and (y == 2 or y == 3 or y == 4)) or
            (y == 2 and (x == 2 or x == 3 or x == 4)) or 
            (x == 3 and y == 3)) {
            as = "IMPOSSIBLE";
        }


        cout << "Case #" << T << ": " << as << '\n';
        if (as == "IMPOSSIBLE") {
            continue;
        }
        cout << ans[x][y];
    }
    return 0;
}
