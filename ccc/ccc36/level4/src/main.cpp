#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int dx[5] = {+1, -1, +0, +0};
int dy[5] = {+0, +0, +1, -1};

int h, w;

map<char, int> dir_lookup = {
        {'R', 2},
        {'L', 3},
        {'U', 1},
        {'D', 0}
};

string dir_to_char = "DURL";

vector<string> board;
int num_collected;

struct Point {
    int x, y;

    void read() {
        cin >> x >> y;
        x -= 1;
        y -= 1;
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

    Point move_in(int dir) {
        return Point{
                this->x + dx[dir],
                this->y + dy[dir]
        };
    }

    bool valid() {
        return board[x][y] != 'W' && board[x][y] != 'G';
    }

    bool has_coin() {
        return board[x][y] == 'C';
    }

    void collect() {
        if (has_coin()) {
            num_collected++;
            board[x][y] = '.';
        } else {
            throw "invalid";
        }
    }
};

Point pac;


vector<int> nearest() {
    vector<vector<int>> visited(h, vector<int>(w, -1));
    queue<Point> q;
    q.push(pac);
    visited[pac.x][pac.y] = -2;

    Point solution;
    vector<int> moves;

    while (!q.empty()) {
        auto now = q.front();
        q.pop();

        if (now.has_coin()) {
            solution = now;
            break;
        }

        for (int d = 0; d < 4; d += 1) {
            auto next = now.move_in(d);
            if (!next.valid()) {
                continue;
            }

            if (visited[next.x][next.y] == -1) {
                visited[next.x][next.y] = d;
                q.push(next);
            }
        }
    }

    // go back from solution to start
    while (true) {
        // is start
        int d = visited[solution.x][solution.y];
        if (d == -2) {
            break;
        }

        moves.push_back(d);
        solution = solution.move_in(d ^ 1);
    }

    return moves;
}

int main() {
    cin >> h;
    board.resize(h);
    for (auto &itr: board) {
        cin >> itr;
    }

    w = board[0].size();

    pac.read();

    int max_moves;
    cin >> max_moves;

//    int num_ghosts;
//    cin >> num_ghosts;
//    vector<Point> ghosts(num_ghosts);
//    vector<string> ghost_moves(num_ghosts);
//    for (int i = 0; i < num_ghosts; i += 1) {
//        ghosts[i] = Point::read();
//        cin >> aux;
//        cin >> ghost_moves[i];
//    }

    vector<int> next_moves;
    while (true) {
        if (next_moves.size()) {
            int d = next_moves.back();
            next_moves.pop_back();

            pac = pac.move_in(d);
            if (!pac.valid()) {
                cerr << "ERROR 1!\n";
                return 0;
            }

            cout << dir_to_char[d];
            if (pac.has_coin()) {
                pac.collect();
            }

            continue;
        }

        bool empty = true;
        for (int i = 0; i < h; i += 1) {
            for (int j = 0; j < w; j += 1) {
                if (board[i][j] == 'C') {
                    empty = false;
                }
            }
        }
        if (empty) {
            break;
        }

        // try to move in one direction if available
        bool collected = false;
        for (int d = 0; d < 4; d += 1) {
            auto newPac = pac.move_in(d);
            if (!newPac.valid()) {
                continue;
            }
            if (newPac.has_coin()) {
                cout << dir_to_char[d];
                pac = newPac;
                pac.collect();
                collected = true;
                break;
            }
        }

        if (collected) {
            continue;
        } else {
            next_moves = nearest();
        }
    }

    cout << '\n';

//    int ans = 0;
//    bool dead = false;
//    for (int i = 0; i < num_moves; i += 1) {
//        bool ok = pac.advance(pac_moves[i]);
//        if (!ok) {
//            dead = true;
//            break;
//        }
//
//        for (int g = 0; g < num_ghosts; g += 1) {
//            ghosts[g].advance(ghost_moves[g][i]);
//            if (ghosts[g].x == pac.x && ghosts[g].y == pac.y) {
//                dead = true;
//            }
//        }
//
//        if (dead) {
//            break;
//        }
//
//        if (board[pac.x][pac.y] == 'C') {
//            ans += 1;
//        }
//        board[pac.x][pac.y] = '.';
//    }

//    cout << ans << ' ';
//    if (!dead) {
//        cout << "YES\n";
//    } else {
//        cout << "NO\n";
//    }

    return 0;
}