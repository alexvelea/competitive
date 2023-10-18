#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int kMaxN = 100, kMaxSteps = 1000;

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

vector<int> all_dirs = {0, 3, 2, 1};

bool has_ghost[kMaxN][kMaxN][kMaxSteps];

int h, w;

string dir_to_char = "DURL";
map<char, int> dir_lookup = {
        {'R', 2},
        {'L', 3},
        {'U', 1},
        {'D', 0}
};

vector<string> board;

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

    Point move_in(int dir) const {
        return Point{
                this->x + dx[dir],
                this->y + dy[dir]
        };
    }

    bool has_wall() const {
        return board[x][y] == 'W';
    }

    bool has_coin() {
        return board[x][y] == 'C';
    }
};

Point pac;
vector<Point> coins;

struct State {
    Point p;
    int steps, config;
    int prevDir;

    string toString() const {
        return
                to_string(p.x) + "@" +
                to_string(p.y) + "@" +
                to_string(steps) + "@" +
                to_string(config)
                + "@" + to_string(prevDir);
    }
    string small() const {
        return
                to_string(p.x) + "@" +
                to_string(p.y) + "@" +
                to_string(steps) + "@" +
                to_string(config);
    }
};

vector<int> bfs() {
    map<string, bool> visited;
    map<string, State> from;
    queue<State> q;
    auto initial = State({pac, 0, 0, 0});
    q.push(initial);
    visited[initial.toString()] = true;

    State solution{};

    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        cerr << now.small() << '\n';

        if (now.config == ((1 << int(coins.size())) - 1)) {
            solution = now;
            break;
        }

        for (auto d: all_dirs) {
            State next = {
                    now.p.move_in(d),
                    now.steps + 1,
                    now.config,
                    d,
            };


            if (has_ghost[next.p.x][next.p.y][next.steps]) {
                continue;
            }
            if (next.p.has_wall()) {
                continue;
            }
            if (visited[next.toString()]) {
                continue;
            }

            for (int i = 0; i < (int) coins.size(); i += 1) {
                if (coins[i].x == next.p.x && coins[i].y == next.p.y) {
                    next.config |= (1 << i);
                }
            }

            visited[next.toString()] = true;
            from[next.toString()] = now;
            q.push(next);
        }
    }

    vector<int> moves;

    // go back from solution to start
    while (true) {
        if (solution.steps == 0) {
            break;
        }

        moves.push_back(solution.prevDir);
        solution = from[solution.toString()];
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

    for (int i = 0; i < h; i += 1) {
        for (int j = 0; j < w; j += 1) {
            if (board[i][j] == 'C') {
                coins.push_back(Point({i, j}));
            }
        }
    }

    pac.read();

    int num_ghosts;
    cin >> num_ghosts;
    ghosts.resize(num_ghosts);
    for (auto &itr: ghosts) {
        itr.read();
        for (int i = 0; i < kMaxSteps; i += 1) {
            has_ghost[itr.x][itr.y][i] = true;
            itr.advance();
        }
    }

    int max_moves;
    cin >> max_moves;

    auto moves = bfs();
    reverse(moves.begin(), moves.end());
    for (auto itr: moves) {
        cout << dir_to_char[itr];
    }
    cout << '\n';

    return 0;
}