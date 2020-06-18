#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxN = 1e5;


int dx[4] = {+1, +0, -1, +0};
int dy[4] = {+0, +1, +0, -1};

int main() {
    int h, w; cin >> h >> w;
    int x, y; cin >> x >> y;
    cout << x << ' ' << y << '\n';
    int direction = 0;

    char option; int num;
    while (cin >> option) {
        cin >> num;
        if (option == 'F') {
            for (int i = 0; i < num; i += 1) {
                x += dx[direction];
                y += dy[direction];
                cout << x << ' ' << y << '\n';
            }
        } else {
            direction += num;
            direction %= 4;
        }
    }

    return 0;
}

