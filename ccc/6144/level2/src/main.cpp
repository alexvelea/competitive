#include "debug.hpp"

using namespace std;

int dx[6] = {-1, -1, 0, +1, +1, 0};
int dy[6] = {-1, +1, +2, +1, -1, -2};


int main() {
    int t; cin >> t;
    string S;
    getline(cin, S);
    getline(cin, S);

    while (t--) {
        int ans = 0;
        vector<string> s;


        while (1) {
            getline(cin, S);
            if (S == "\n" || S == "" || S == "\r") {
                break;
            }
            s.push_back(S.substr(0, S.size()-1));
        }

        int n = s.size();
        int m = s[0].size();

        int x, y;
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < m; j += 1) {
                if (s[i][j] == 'W') {
                    x = i;
                    y = j;
                }
            }
        }

        Debug(n, m, x, y);

        for (int d = 0; d < 6; d += 1) {
            int nx = dx[d] + x;
            int ny = dy[d] + y;

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (s[nx][ny] == 'O') {
                    ans += 1;
                }
            }
        }

        cout << ans << '\n';
    }
}