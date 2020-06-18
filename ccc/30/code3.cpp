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

void Solve(string input, int id, int q_time, int start_time, int start_x, int start_y, double speed) {
    int direction = 0;
    double x = start_x;
    double y = start_y;

    stringstream cin; cin << input << '\n';

    int c_time = 0;
    char option; int num;

    cerr << "#@!#@!\n";
    cerr << q_time << '\n';

    int req_time = (q_time - start_time) * speed;

    while (cin >> option) {
        cin >> num;
        if (option == 'F') {
            for (int i = 0; i < num; i += 1) {
                if (c_time == req_time) {
                    cout << q_time << ' ' << id << ' ' << int(x + 1e-7) << ' ' << int(y + 1e-7) << '\n';
                    return;
                }          

                x += dx[direction];
                y += dy[direction];

                c_time += 1;
            }
        } else {
            direction += num;
            direction %= 4;
        }
    }
    
    cout << q_time << ' ' << id << ' ' << int(x + 1e-7) << ' ' << int(y + 1e-7) << '\n';
}

int main() {
    int h, w; cin >> h >> w;
    int x, y; cin >> x >> y;

    string input; 
    getline(cin, input);
    getline(cin, input);

    double speed; cin >> speed;
    int n; cin >> n;
    vector<int> start_time(n);
    for (auto& itr : start_time) { 
        cin >> itr;
    }

    int q; cin >> q;
    while (q--) {
        int time, id;
        cin >> time >> id;
        Solve(input, id, time, start_time[id], x, y, speed);
    }

    return 0;
}

