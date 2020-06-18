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

void Fail() {
    cout << current_tick << '\n';
    cout << "LOSS\n";
    exit(0);
}

void Finish() {
    cout << current_tick << '\n';
    cout << "WIN\n";
    exit(0);
}

vector<Update> updates;

vector<pair<int, int>> board_positions;

struct Allien {
    Allien(int id, int spawn_time, int x, int y, double health, double speed) //
          : id(id), spawn_time(spawn_time), x(x), y(y), health(health), speed(speed) {
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
    int spawn_time;

    int target_id = -1;

    bool CanShoot() {
        return current_tick > spawn_time;
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
};

vector<Tower> towers;

int main() {
    int h, w; cin >> h >> w;
    int x, y; cin >> x >> y;

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

        while (ss >> option) {
            ss >> num;
            updates.push_back({option == 'F', num});

            // weird stuff here
            if (option == 'F') {
                for (int i = 0; i < num; i += 1) {
                    x += dx[direction];
                    y += dy[direction];
                    board_positions.push_back({x, y});
                }
            } else {
                direction += num;
                direction %= 4;
            }
        }
    }

    double health, speed; cin >> health >> speed;
    
    int n; cin >> n;
    for (int i = 0; i < n; i += 1) {
        int spawn_time; cin >> spawn_time;
        alliens.push_back({i, spawn_time, x, y, health, speed});
    }

    double damage, range; cin >> damage >> range;
    int num_towers; cin >> num_towers;

    for (int i = 0; i < num_towers; i += 1) {
        int spawn_time;
        double x, y; cin >> x >> y >> spawn_time;
        towers.push_back({i, x, y, damage, range, spawn_time});
    }


    while (1) {
        cerr << current_tick << '\n';
        for (auto& allien : alliens) {
            allien.ApplyUpdate();
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
        }

        // See if alliens dead
        for (auto& allien : alliens) {
            if (allien.health - 1e-7 < 0) {
                allien.is_dead = true;
            }
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

    return 0;
}

