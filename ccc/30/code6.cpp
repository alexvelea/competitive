#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

typedef long long int64;

const int kMaxN = 1e5;

int dx[4] = {+1, +0, -1, +0};
int dy[4] = {+0, +1, +0, -1};

struct Update {
    int is_move;
    int num;
};

int current_tick = 0;
bool is_simulation_done = false;
bool is_win = false;

void Fail() {
/*    
    cerr << current_tick << '\n';
    cerr << "LOSS\n";   
*/
    is_simulation_done = true;
    is_win = false;
}

vector<Update> updates;

vector<pair<int, int>> board_positions;


int start_x, start_y;
double start_health, start_speed;

struct Allien {
    Allien(int id, int spawn_time, int x, int y, double health, double speed) //
          : id(id), spawn_time(spawn_time), x(x), y(y), health(health), speed(speed) {
              is_dead = false;
              update_id = 0;
              progress_distance = 0.0;
    }

    int id;
    int spawn_time;

    double x, y;
    int direction;
    double health;
    double speed;

    bool is_dead;

    int update_id;
    double progress_distance;

    void Reset() {
        x = start_x;
        y = start_y;
        direction = 0;
        health = start_health;
        speed = start_speed;
        
        is_dead = false;
        update_id = 0;
        progress_distance = 0;
    }

    void NextUpdate() {
        update_id += 1;
        progress_distance = 0;
    }

    bool IsSpawned() {
        return current_tick >= spawn_time;
    }

    void ApplyUpdate() {
        if (is_dead) { 
            return;
        }

        if (current_tick <= spawn_time) {
            return;
        }

        int move_id = int((current_tick - spawn_time + 1e-7) * speed);

        if (move_id >= (int)board_positions.size()) {
            Fail();
        }

        x = board_positions[move_id].first;
        y = board_positions[move_id].second;
        return;

        double remaining_ticks = 1.0;
        while (remaining_ticks > 0) {
            // Check for game end
            if (update_id == (int)updates.size()) {
                Fail();
            }

            // current tick move
            if (updates[update_id].is_move == false) {
                direction += updates[update_id].num;
                direction %= 4;
                NextUpdate();
                continue;
            }

            double distance = updates[update_id].num - progress_distance;
            double duration = distance / speed;

            if (duration > remaining_ticks) {
                duration = remaining_ticks;
            }

//            cerr << "Moving allien" << '\t' << id << '\n';
            x += dx[direction] * duration * speed;
            y += dy[direction] * duration * speed;
            
            progress_distance += duration * speed;

            remaining_ticks -= duration;

            if (progress_distance + 1e-7 > updates[update_id].num) {
                NextUpdate();
            }
        }
    }
};

vector<Allien> alliens;

struct Tower {
    int id;
    double x, y;
    double damage;
    double range;
    int spawn_time = 0;

    int target_id = -1;

    bool CanShoot() {
        return current_tick > 0;
    }

    bool MantainTarget() {
        if (target_id == -1) {
            return false;
        }

        return CanShootAt(alliens[target_id]);   
    }

    bool CanShootAt(Allien& a) {
        if (a.is_dead == true) {
            return false;
        }

        if (a.IsSpawned() == false) {
            return false;
        }
        return DistanceTo(a) <= range * range;
    }

    double DistanceTo(Allien& a) {
        double a_x = int(a.x + 1e-7);
        double a_y = int(a.y + 1e-7);
        double distance = ((x - a_x) * (x - a_x) + (y - a_y) * (y - a_y));
        return distance;
    }

    bool operator<(const Tower& rhs) const { return false; }
};

vector<Tower> towers;

void Finish() {
    cerr << "WIN\n\n";
    cerr << current_tick << '\n';

    for (auto& itr : towers) {
        cout << itr.x << ' ' << itr.y << ' ' << itr.spawn_time << '\n';
    }

    is_simulation_done = true;
    is_win = true;
    exit(0);
}

int tower_gold_cost;
int start_num_gold; 
int loot;

vector<Tower> tower_wait_list;

void Simulate() {
    cerr << "Starting simulation\n";
    cerr << "Waiting list:\t" << tower_wait_list.size() << '\n';
    is_simulation_done = false;
    is_win = false;
    current_tick = 0;
    towers.clear();

    int num_gold = start_num_gold;
    reverse(tower_wait_list.begin(), tower_wait_list.end());

    for (auto& allien : alliens) {
        allien.Reset();
    }

    while (is_simulation_done == false) {
        for (auto& allien : alliens) {
            allien.ApplyUpdate();
            if (allien.is_dead == false and allien.IsSpawned() == true) {
            }
        }

        // Set up tower new target
        for (auto& tower : towers) {
            if (not tower.CanShoot()) {
                continue;
            }

            if (tower.MantainTarget()) {
                continue;
            }

            tower.target_id = -1;

            double min_distance = 1e9;
            for (auto& allien : alliens) {
                if (tower.CanShootAt(allien)) {
                    double d = tower.DistanceTo(allien);
                    if (d + 1e-7 < min_distance) {
                        tower.target_id = allien.id;
                        min_distance = d;
                    }
                }
            }
        }

        // Shoot towers
        for (auto& tower : towers) {
            if (tower.target_id == -1) {
                continue;
            }

            alliens[tower.target_id].health -= tower.damage;
//            cerr << "Tower " << tower.id << '\t' << " shoots at " << tower.target_id << '\n';
        }

        // See if alliens dead
        for (auto& allien : alliens) {
            if (allien.health - 1e-7 < 0 and allien.is_dead == false) {
                allien.is_dead = true;
                num_gold += loot;
            }
        }

//        cerr << num_gold << '\t' << towers.size() << '\t' << tower_wait_list.size() << '\n';
        // place new towers
        while (num_gold >= tower_gold_cost and tower_wait_list.size()) {
            num_gold -= tower_gold_cost;
            auto t = tower_wait_list.back();
            tower_wait_list.pop_back();
            t.spawn_time = current_tick;
            towers.push_back(t);
        }

        bool got_any_left = false;
        for (auto& allien : alliens) {
            got_any_left |= (allien.is_dead ^ 1);
        }

        if (not got_any_left) {
            Finish();
        }

        current_tick += 1;
    }

    cerr << "Simulation done!\n";
//    exit(0);
}

int main(int argc, char**) {
    int h, w; cin >> h >> w;
    int x, y; cin >> x >> y;

    start_x = x;
    start_y = y;

    map<pair<int, int>, int> used;

    {
        int start_x = x;
        int start_y = y;

        string input;
        getline(cin, input);
        getline(cin, input);

        stringstream ss;
        ss << input;

        char option;
        int num;

        int direction = 0;
        int x = start_x;
        int y = start_y;

        board_positions.push_back({x, y});

        int last_x = x;
        int last_y = y;

        used[{x, y}] = true;

        while (ss >> option) {
            ss >> num;
            updates.push_back({option == 'F', num});

            // weird stuff here
            if (option == 'F') {
                for (int i = 0; i < num; i += 1) {
                    x += dx[direction];
                    y += dy[direction];
                    used[{x, y}] = true;
                    board_positions.push_back({x, y});
                    if (argc > 1) {
                        cerr << "Segment " << x << ' ' << y << ' ' << last_x << ' ' << last_y << '\n';
                    }
                    last_x = x;
                    last_y = y;
                }
            } else {
                direction += num;
                direction %= 4;
            }
        }
    }

    double health, speed; 
    cin >> health >> speed >> loot;


    start_health = health;
    start_speed = speed;
    
    int n; cin >> n;
    for (int i = 0; i < n; i += 1) {
        int spawn_time; cin >> spawn_time;
        alliens.push_back({i, spawn_time, x, y, health, speed});
    }

    double damage, range; cin >> damage >> range;
    cin >> tower_gold_cost;
    cin >> start_num_gold;

    if (argc > 1) {
        for (int i = 0; i < h; i += 1) {
            for (int j = 0; j < w; j += 1) {
                bool ok = false;
                for (int a = -range; a <= range; a += 1) {
                    for (int b = -range; b <= range; b += 1) {
                        if (used[{i + a, j + b}]) {
                            ok = true;
                        }
                    }
                }

                if (used[{i, j}] == 0 and ok) {
                    cerr << i << ' ' << j << '\n';
                }
            }
        }
        return 0;
    }

    // figure out heat chart
    map<pair<int, int>, int> heat_chart;
    {
        Allien a = alliens[0];
        a.spawn_time = 0;
        while (is_simulation_done == false) {
            heat_chart[{int(a.x + 1e-7), int(a.y + 1e-7)}] += 1;
            a.ApplyUpdate();
            current_tick += 1;
        }
    }

    // figure out tower orders;
    vector<pair<int, Tower>> all_tower_orders;
    for (int i = 0; i < h; i += 1) {
        for (int j = 0; j < w; j += 1) {
/*            
    int id;
    double x, y;
    double damage;
    double range;
*/    
            if (used[{i, j}]) {
                continue;
            }

            Tower t({0, 1.0 * i, 1.0 * j, damage, range});
            int num = 0;
            for (int a = -range; a <= range; a += 1) {
                for (int b = -range; b <= range; b += 1) {
                    // Allien(int id, int spawn_time, int x, int y, double health, double speed) //
                    Allien allien ({0, -1, i + a, j + b, 1.0, 1.0});
                    if (t.CanShootAt(allien)) {
                        num += heat_chart[{i + a, j + b}];
                    }
                }
            }
            if (num > 0) {
                all_tower_orders.push_back({num, t});
            }
        }
    }

    sort(all_tower_orders.begin(), all_tower_orders.end());
    reverse(all_tower_orders.begin(), all_tower_orders.end());


/*
    int num_towers; cin >> num_towers;
    for (int i = 0; i < num_towers; i += 1) {
        double x, y; cin >> x >> y;
        if (used[{x, y}]) {
            cerr << "ERROR TOWER WRONG POS\t" << x << '\t' << y << '\t' << used[{x, y}] << '\n';
        }
        used[{x, y}] = 1;
        towers.push_back({i, x, y, damage, range});
    }   
*/
    srand(time(0));
    // simulate stuff here
    while (1) {
        tower_wait_list.clear();
        int itr = 0;
        double max_cost_offset = 1.0 * rand() / RAND_MAX * 20;

        cerr << "Finding out towers\n";

        while (itr < (int)all_tower_orders.size() and tower_wait_list.size() < 500) {
            auto t = all_tower_orders[itr].second;
            itr += 1;
            
            double cost = 0.0;
            for (auto& q : tower_wait_list) {
                double dist = (t.x - q.x) * (t.x - q.x) + (t.y - q.y) * (t.y - q.y);
                if (dist > range * range) {
                    continue;
                } else {
                    cost += range * range - dist;
                }
            }

            if (cost > max_cost_offset * range * range) {
                continue;
            }

            tower_wait_list.push_back(t);
        }

        Simulate();
    }
    return 0;
}

