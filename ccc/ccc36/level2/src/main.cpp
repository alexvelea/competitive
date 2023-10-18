#include <iostream>
#include <vector>
#include <map>

using namespace std;

int dx[5] = {0, +1, -1, +0, +0};
int dy[5] = {0, +0, +0, +1, -1};

map<char, int> dir_lookup = {
        {'R', 3},
        {'L', 4},
        {'U', 2},
        {'D', 1}
};

int main() {
    int h;
    cin >> h;
    vector<string> board(h);
    for (auto &itr: board) {
        cin >> itr;
    }

    int w = board[0].size();
    int x, y;
    cin >> x >> y;
    x -= 1;
    y -= 1;

    int aux; cin >> aux;
    string moves;
    cin >> moves;
    int ans = 0;
    for (char itr: moves) {
        int d = dir_lookup[itr];
        x += dx[d];
        y += dy[d];
//        cout << x << '\t' << y << '\n';
        if (board[x][y] == 'C') {
            ans += 1;
        }
        board[x][y] = '.';
    }

    cout << ans << '\n';
    return 0;
}