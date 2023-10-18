#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

template<class RandomIt>
void random_shuffle(RandomIt first, RandomIt last) {
    typename std::iterator_traits<RandomIt>::difference_type i, n;
    n = last - first;
    for (i = n - 1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[std::rand() % (i + 1)]);
        // rand() % (i+1) isn't actually correct, because the generated number
        // is not uniformly distributed for most values of i. A correct implementation
        // will need to essentially reimplement C++11 std::uniform_int_distribution,
        // which is beyond the scope of this example.
    }
}

int dx[5] = {+1, -1, +0, +0};
int dy[5] = {+0, +0, +1, -1};

vector<int> all_dirs = {0, 1, 2, 3};

int h, w;

string dir_to_char = "DURL";
map<char, int> dir_lookup = {
        {'R', 2},
        {'L', 3},
        {'U', 1},
        {'D', 0}
};

vector<string> board;
int num_collected;

struct Ghost {
    int x{}, y{};
    vector<int> directions;
    int dir = 0;

    void read() {
        cin >> x >> y;
        x -= 1;
        y -= 1;
        int size;
        cin >> size;
        for (int i = 0; i < size; i += 1) {
            char c;
            cin >> c;
            directions.push_back(dir_lookup[c]);
        }
    }

    void advance() {
        if (dir == int(directions.size())) {
            reverse();
        }

        x += dx[directions[dir]];
        y += dy[directions[dir]];

        dir += 1;
    }

    void reverse() {
        dir = 0;
        ::reverse(directions.begin(), directions.end());
        for (auto &itr: directions) {
            itr ^= 1;
        }
    }
};

vector<Ghost> ghosts;

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

    bool valid() const {
        if (board[x][y] == 'W') {
            return false;
        }

        for (auto &itr: ghosts) {
            if (itr.x == x && itr.y == y) {
                return false;
            }
        }

        return true;
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

        random_shuffle(all_dirs.begin(), all_dirs.end());
        for (auto d: all_dirs) {
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
    srand(time(nullptr));

    cin >> h;
    board.resize(h);
    for (auto &itr: board) {
        cin >> itr;
    }

    w = board[0].size();

    pac.read();

    int num_ghosts;
    cin >> num_ghosts;
    ghosts.resize(num_ghosts);
    for (auto &itr: ghosts) {
        itr.read();
    }

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

    int last_move = 0;
    int num_moves = 0;
    while (true) {
        num_moves += 1;
        if (num_moves > max_moves) {
            cerr << "ERROR MAX MOVES!\n";
            return 0;
        }

        // advance ghosts
        for (auto &g: ghosts) {
            g.advance();
        }

        auto moves = nearest();

        if (moves.empty() || rand() % 2 == 0) {
            // do last move instead
            auto newPac = pac.move_in(last_move);
            if (newPac.valid()) {
                pac = newPac;
                cout << dir_to_char[last_move];

                if (pac.has_coin()) {
                    cerr << "HAS COIN!\n";
                    break;
                }
                continue;
            }
        }

        if (moves.empty()) {
            bool ok = false;
            for (auto d: all_dirs) {
                auto next = pac.move_in(d);
                if (next.valid()) {
                    pac = next;
                    ok = true;
                    break;
                }
            }

            if (ok == false) {
                cerr << "ERROR empty moves\n";
                return 0;
            } else {
                continue;
            }

        }

        int d = moves.back();
        last_move = d;
        cout << dir_to_char[d];

        pac = pac.move_in(d);
        if (pac.has_coin()) {
            cerr << "HAS COIN!\n";
            break;
        }

//        if (next_moves.size()) {
//            int d = next_moves.back();
//            next_moves.pop_back();
//
//            pac = pac.move_in(d);
//            if (!pac.valid()) {
//                cerr << "ERROR 1!\n";
//                return 0;
//            }
//
//            cout << dir_to_char[d];
//            if (pac.has_coin()) {
//                pac.collect();
//            }
//
//            continue;
//        }
//
//        bool empty = true;
//        for (int i = 0; i < h; i += 1) {
//            for (int j = 0; j < w; j += 1) {
//                if (board[i][j] == 'C') {
//                    empty = false;
//                }
//            }
//        }
//        if (empty) {
//            break;
//        }
//
//        // try to move in one direction if available
//        bool collected = false;
//        for (int d = 0; d < 4; d += 1) {
//            auto newPac = pac.move_in(d);
//            if (!newPac.valid()) {
//                continue;
//            }
//            if (newPac.has_coin()) {
//                cout << dir_to_char[d];
//                pac = newPac;
//                pac.collect();
//                collected = true;
//                break;
//            }
//        }
//
//        if (collected) {
//            continue;
//        } else {
//            next_moves = nearest();
//        }
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