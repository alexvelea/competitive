// solar shit
/* 
    swap(n, m);
    int t; cin >> t;
    while (t--) {
        map<pair<int, int>, int> inside;

        double ox, oy; cin >> ox >> oy;
        int vx, vy; cin >> vx >> vy;
        bool swapped = false;
        
        if (abs(vx) > abs(vy) || abs(vx) == abs(vy)) {
            ;
        } else {
            swap(n, m);
            swap(ox, oy);
            swap(vx, vy);
            swapped = true;
        }

        int sign_x = (vx >= 0) ? +1 : -1;
        int sign_y = (vy >= 0) ? +1 : -1;
    
        auto GetCell = [&](double x, double y) -> pair<int, int> {
            return {
                int(x + 0.5 + eps), int(y + 0.5 + eps)
            };
        };

        auto Add = [&](double x, double y) -> void {
            auto c = GetCell(x, y);
            if (inside[c]) { return; }
            inside[c] = true;
            

            if (c.first < 0 || c.first >= n || c.second < 0 || c.second >= m) {
                return;
            }

            if (swapped) {
                swap(c.first, c.second);
            }

            cout << c.first << ' ' << c.second << ' ';
//            cerr << "????" << ox << '\t' << oy << '\t' << x << '\t' << y << '\n';
        };

        while (1) {
            if (ox < -0.5 || ox > n + 0.5 || oy < -0.5 || oy > m + 0.5) {
                break;
            }
    
            bool x_int = false;
            if (abs((ox + 0.5) - int(ox + 0.5 + eps)) < eps) {
                x_int = true;
            }

            bool y_int = false;
            if (abs((oy + 0.5) - int(oy + 0.5 + eps)) < eps) {
                y_int = true;
            }
            
            if (x_int and y_int) {
            }

            double q = abs(vx) * 100;
                Add(ox - sign_x * 1.0 / q, oy - sign_y * 1.0 / q);
                Add(ox + sign_x * 1.0 / q, oy - sign_y * 1.0 / q);
                Add(ox - sign_x * 1.0 / q, oy + sign_y * 1.0 / q);
                Add(ox + sign_x * 1.0 / q, oy + sign_y * 1.0 / q);
            
            ox += 0.5 * vx / abs(vx);
            oy += 0.5 * vy / abs(vx);
        }

        cout << '\n';

        if (swapped) {
            swap(n, m);
        }
    }
    return 0;
*/

#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long int64;

const double eps = 1e-7;
const int kMaxN = 1e3 + 5;
const int kMaxCountry = 1e6+7;

int country_id[kMaxN][kMaxN];
bool on_border[kMaxN][kMaxN];

vector<pair<int, int>> cells[kMaxCountry];
pair<int, int> capital[kMaxCountry];
vector<int> neighbours[kMaxCountry];

int dx[4] = {0, 0, +1, -1};
int dy[4] = {-1, +1, 0,0}; 


int num_countries = 0;

int EucDistance(int a, int b) {
    auto& A = capital[a];
    auto& B = capital[b];
    return sqrt( (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second));
}

int Distance(int source, int dest) {
    vector<int> min_distnce(num_countries, 1e9);
    min_distnce[source] = 0;
    priority_queue<pair<int, int>> bfs;

    bfs.push({0, source});

    while (bfs.size()) {
        auto top = bfs.top();
        bfs.pop();
        
        if (-top.first != min_distnce[top.second]) {
            continue;
        }

        int my = top.second;
        int cost = -top.first;

        for (auto oth : neighbours[my]) {
            int n_cost = cost + EucDistance(my, oth);
            if (n_cost < min_distnce[oth]) {
                min_distnce[oth] = n_cost;
                bfs.push({-n_cost, oth});
            }
        }
    }

    return min_distnce[dest];
}

int main() {
    int num_solar_pannels; cin >> num_solar_pannels;
    vector<pair<int, int>> solar_pannels;
    for (int i = 0; i < num_solar_pannels; i += 1) {
        int id, price; cin >> id >> price;
        solar_pannels.push_back({id, price});
    }

    int n, m; cin >> n >> m;
    for (int j = 1; j <= m; j += 1) {
        for (int i = 1; i <= n; i += 1) {
            int x; cin >> x;
            int c; cin >> c;
            country_id[i][j] = c;
            num_countries = max(num_countries, c + 1);
            cells[c].push_back({i, j});
        }
    }

    for (int i = 1; i <= n; i += 1) {
        country_id[i][0] = -1;
        country_id[i][m + 1] = -1;
    }

    for (int i = 1; i <= m; i += 1) {
        country_id[0][i] = -1;
        country_id[n + 1][i] = -1;
    }

    map<int, int> ans;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            bool ok = false;
            int my_id = country_id[i][j];
            for (int d = 0; d < 4; d += 1) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                if (country_id[nx][ny] != my_id) {
                    ok = true;
                    if (country_id[nx][ny] != -1) {
                        neighbours[my_id].push_back(country_id[nx][ny]);
                    }
                }
            }

            if (ok) {
                ans[country_id[i][j]] += 1;
                on_border[i][j] = true;
            }
        }
    }

    for (int i = 0; i < num_countries; i += 1) {
        auto& cells = ::cells[i];
        int64 x = 0, y = 0;
        for (auto cell : cells) {
            x += cell.first;
            y += cell.second;
        }

        x /= cells.size();
        y /= cells.size();

        vector<pair<int, pair<int, int>>> p_cells;
        for (auto cell : cells) {
            if (on_border[cell.first][cell.second]) {
                continue;
            }

            p_cells.push_back({
                    (x - cell.first) * (x - cell.first) + 
                    (y - cell.second) * (y - cell.second), {
                    cell.second, cell.first} });
        }

        sort(p_cells.begin(), p_cells.end());
        capital[i] = p_cells[0].second;
    }

    for (int i = 0; i < num_countries; i += 1) {
        sort(neighbours[i].begin(), neighbours[i].end());
        neighbours[i].resize(unique(neighbours[i].begin(), neighbours[i].end()) - neighbours[i].begin());
    }

    for (int i = 0; i < num_countries; i += 1) {
        for (int j = 0; j < num_solar_pannels; j += 1) {
            cout << solar_pannels[j].second + Distance(i, solar_pannels[j].first) << ' ';
        }
        cout << '\n';
    }
}
