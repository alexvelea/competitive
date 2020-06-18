// solar shit
/* 
    swap(n, m);
    int t; cin >> t;
    while (t--) {
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
const int kMaxCountry = 1e4+7;

int n, m; 
int height[kMaxN][kMaxN];
int country_id[kMaxN][kMaxN];
bool on_border[kMaxN][kMaxN];
bool can_have_solar_panel[kMaxN][kMaxN];
int num_solar_hours[kMaxN][kMaxN];

vector<pair<int, int>> cells[kMaxCountry];
pair<int, int> capital[kMaxCountry];
vector<int> neighbours[kMaxCountry];

int dx[4] = {0, 0, +1, -1};
int dy[4] = {-1, +1, 0,0}; 

int extended_dx[8] = {+1, +1, +1, 0, 0, -1, -1, -1};
int extended_dy[8] = {-1, 0, +1, +1, -1, -1, 0, +1};

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

struct Ray {
    int x, y, z;
}; 

struct SolarPanel {
    int uid; 
    int id, cost, bonus;
};


        vector<pair<int, pair<int, int>> > good_cells[kMaxCountry];
 

vector<pair<int, int>> IntersectRay(double ox, double oy, int vx, int vy) {
    swap(n, m);

        map<pair<int, int>, int> inside;
        vector<pair<int, int>> ans;

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

            ans.push_back(c);
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

        if (swapped) {
            swap(n, m);
        }

    swap(n, m);
    return ans;
}


void FixSun(Ray r) {
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            if (can_have_solar_panel[i][j] == false) {
                continue;
            }

            auto v = IntersectRay(j - 1, i - 1, -r.x, -r.z);
            v = vector<pair<int, int>>(v.begin() + 1, v.end());
            bool ok = true;
            for (auto p : v) {
                int x = p.first;
                int z = p.second;
                int y = height[z + 1][x + 1];

                double n_x = x - 0.5;
                double n_z = (n_x - 1.0 * (j - 1)) / r.x * r.z + (i - 1);
                double n_y = (n_x - 1.0 * (j - 1)) / r.x * r.y + height[i][j];
                if (n_z >= z - 0.5 && n_z <= z + 0.5 && n_y <= y) { ok = false; }

                {
                double n_x = x + 0.5;
                double n_z = (n_x - 1.0 * (j - 1)) / r.x * r.z + (i - 1);
                double n_y = (n_x - 1.0 * (j - 1)) / r.x * r.y + height[i][j];
                if (n_z >= z - 0.5 && n_z <= z + 0.5 && n_y <= y) { ok = false; }
                }

                {
                double n_z = z - 0.5;
                double n_x = (n_z - 1.0 * (i - 1)) / r.z * r.x + (j - 1);
                double n_y = (n_z - 1.0 * (i - 1)) / r.z * r.y + height[i][j];
                if (n_x >= x - 0.5 && n_x <= x + 0.5 && n_y <= y) { ok = false; }
                }

                {
                double n_z = z + 0.5;
                double n_x = (n_z - 1.0 * (i - 1)) / r.z * r.x + (j - 1);
                double n_y = (n_z - 1.0 * (i - 1)) / r.z * r.y + height[i][j];
                if (n_x >= x - 0.5 && n_x <= x + 0.5 && n_y <= y) { ok = false; }
                }
            }

            num_solar_hours[i][j] += ok;
        }
    }
}

    vector<SolarPanel> solar_pannels;

int main() {
    int num_hours; cin >> num_hours;
    vector<Ray> sun_rays(num_hours);
    for (auto& itr : sun_rays) {
        cin >> itr.x >> itr.y >> itr.z;
    }


    int num_solar_pannels; cin >> num_solar_pannels;
    for (int i = 0; i < num_solar_pannels; i += 1) {
        int id, price, bonus; cin >> id >> price >> bonus;
        solar_pannels.push_back({i, id, price, bonus});
    }

    cin >> num_countries;
    vector<int> budget(num_countries);
    for (auto& itr : budget) { cin >> itr; }

    int target; cin >> target;

    cin >> n >> m;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            int x; cin >> x;
            int c; cin >> c;
            height[i][j] = x;
            country_id[i][j] = c;
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

    srand(time(0));

/*
    for (int i = 0; i < num_countries; i += 1) {
        for (int j = 0; j < num_solar_pannels; j += 1) {
            cout << solar_pannels[j].second + Distance(i, solar_pannels[j].first) << ' ';
        }
        cout << '\n';
    }
*/

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            bool ok = true;
            for (int d = 0; d < 8 && ok; d += 1) {
                int nx = i + extended_dx[d];
                int ny = j + extended_dy[d];

                if (nx == 0 || nx == n + 1 || ny == 0 || ny == m + 1) {
                    ok = false;
                    break;
                }

                if (country_id[nx][ny] != country_id[i][j] || on_border[nx][ny] == true) {
//                    cerr << "BAd country ID!\n";
                    ok = false;
                    break;
                }

                if (height[nx][ny] != height[i][j]) {
//                    cerr << "bad height!\n";
                    ok = false;
                    break;
                }
            }

            can_have_solar_panel[i][j] = ok;
        }
    }

    for (auto ray : sun_rays) {
        FixSun(ray);
    }

    vector<pair<int, int> > ans_hours;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            if (can_have_solar_panel[i][j] == false) {
                continue;
            }

            ans_hours.push_back(
                    {i, j});
        }
    }

    sort(ans_hours.begin(), ans_hours.end(), [&](auto a, auto b) {
        int A = country_id[a.first][a.second];
        int B = country_id[b.first][b.second];
        int a_h = num_solar_hours[a.first][a.second];
        int b_h = num_solar_hours[b.first][b.second];
        
        if (A != B) { return A < B; };
        if (a_h != b_h) { return a_h > b_h; };
        
        return a < b;
    });
/*
    for (auto& itr : ans_hours) {
        cout << itr.second - 1 << ' ' << itr.first - 1 << ' ' << num_solar_hours[itr.first][itr.second] << '\n';  
    }
*/   
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            int id = country_id[i][j];

            if (num_solar_hours[i][j] == 0) {
                continue;
            }

            good_cells[id].push_back({
                    num_solar_hours[i][j], {i, j}});
        }
    }

    for (int i = 0; i < num_countries; i += 1) {
        sort(good_cells[i].begin(), good_cells[i].end());
        reverse(good_cells[i].begin(), good_cells[i].end());
    }

    struct GameOptions {
        vector<int> budget;
        map<int, pair<int, int>> where;

        vector<SolarPanel> here[kMaxCountry];

        GameOptions(vector<int>& budget) : budget(budget) { 
        }

        bool Add(SolarPanel a, int countr_id) {

            if (where.count(a.uid)) { return false; }
            if (here[countr_id].size() == good_cells[countr_id].size()) { return false; }

            int cost = Distance(a.id, countr_id) + a.cost;
            if (cost > budget[countr_id]) {
                return false;
            }

            here[countr_id].push_back(a);
            budget[countr_id] -= cost;
            cerr << "Added " << a.bonus << '\t' << countr_id << '\t' << cost << '\n';
            return true;
        }

        int GetCost() {
            int ans = 0;

            for (int c = 0; c < num_countries; c += 1) {
                sort(here[c].begin(), here[c].end(), [&](auto a, auto b) { return a.bonus > b.bonus; });
                
                for (int i = 0; i < (int)min(here[c].size(), good_cells[c].size()); i += 1) {
                    ans += here[c][i].bonus * good_cells[c][i].first;
                    where[here[c][i].uid] = good_cells[c][i].second;
                }
            }

           return ans; 
        }

        void Print() {
            for (int i = 0; i < (int)solar_pannels.size(); i += 1) {
                if (where.count(i)) {
                    cout << where[i].second - 1 << ' ' << where[i].first - 1 << '\n';
                } else {
                    cout << -1 << '\n';
                }
            }
        }

        void Stats() {
            for (int i = 0; i < num_countries; i += 1) {
                if (good_cells[i].size() == 0) { continue; }
                cerr << i << '\t' << budget[i] << '\t' << here[i].size() << '\t' << good_cells[i].size() << '\n'; 
            }
        }
    };

    GameOptions go(budget);

    vector<pair<int, int> > all_good_cells;
    vector<SolarPanel> all_solar_panels = solar_pannels;

    for (int i = 0; i < num_countries; i += 1) {
        for (auto& itr : good_cells[i]) {
            all_good_cells.push_back({-itr.first, i});
        }
    }

    sort(all_good_cells.begin(), all_good_cells.end());
    sort(all_solar_panels.begin(), all_solar_panels.end(), [&](auto a, auto b) { 
            return 1.0 * a.bonus * a.bonus / a.cost > 1.0 * b.bonus * b.bonus / b.cost;
    });

    cerr << "Do not move!\n";
    vector<int> countries(num_countries);
    for (int i = 0; i < num_countries; i += 1) {
        countries[i] = i;
    }
    random_shuffle(countries.begin(), countries.end());
    for (auto i : countries) { 
        vector<SolarPanel> here;
        for (auto& itr : solar_pannels) {
            if (itr.id == i) {
                here.push_back(itr);
            }
        }

        sort(all_solar_panels.begin(), all_solar_panels.end(), [&](auto a, auto b) {
            auto c1 = Distance(a.id, i) + a.cost;
            auto c2 = Distance(b.id, i) + b.cost;
            return 1.0 * a.bonus / c1 > 1.0 * b.bonus / c2;
        });

        for (auto& itr : all_solar_panels) {
            if (go.Add(itr, i)) {
                ;
            }
        }
        cerr << '\n';
    }

    go.Stats();

    sort(all_solar_panels.begin(), all_solar_panels.end(), [&](auto a, auto b) { return 1.0 * a.bonus / a.cost > 1.0 * b.bonus / b.cost; });

    cerr << "OTher!\n";
    for (auto& itr : all_solar_panels) {
        for (int i = 0; i < num_countries; i += 1) {
            if (go.Add(itr, i)) {
                cerr << "Added to " << i << '\n';
                break;
            }
        }
    }
    
    go.Stats();

    cerr << go.GetCost() << '\t' << target << '\n';
    go.Print();
}
