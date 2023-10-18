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

vector<string> board;

struct Point {
    int x, y;

    static Point read() {
        Point p{};
        cin >> p.x >> p.y;
        p.x -= 1;
        p.y -= 1;

        return p;
    }

    bool advance(char dir) {
        int d = dir_lookup[dir];

        x += dx[d];
        y += dy[d];
        if (board[x][y] == 'W') {
            return false;
        }
        return true;
    }
};

int main() {
    int h;
    cin >> h;
    board.resize(h);
    for (auto &itr: board) {
        cin >> itr;
    }

    int w = board[0].size();

    Point pacman = Point::read();
    int aux;
    cin >> aux;
    string pac_moves;
    cin >> pac_moves;

    int num_ghosts;
    cin >> num_ghosts;
    vector<Point> ghosts(num_ghosts);
    vector<string> ghost_moves(num_ghosts);
    for (int i = 0; i < num_ghosts; i += 1) {
        ghosts[i] = Point::read();
        cin >> aux;
        cin >> ghost_moves[i];
    }

    int num_moves = pac_moves.size();

    int ans = 0;
    bool dead = false;
    for (int i = 0; i < num_moves; i += 1) {
        bool ok = pacman.advance(pac_moves[i]);
        if (!ok) {
            dead = true;
            break;
        }

        for (int g = 0; g < num_ghosts; g += 1) {
            ghosts[g].advance(ghost_moves[g][i]);
            if (ghosts[g].x == pacman.x && ghosts[g].y == pacman.y) {
                dead = true;
            }
        }

        if (dead) {
            break;
        }

        if (board[pacman.x][pacman.y] == 'C') {
            ans += 1;
        }
        board[pacman.x][pacman.y] = '.';
    }

    cout << ans << ' ';
    if (dead == false) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}