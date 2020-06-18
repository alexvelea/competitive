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
    int x, y; cin >> x >> y;
    int direction = 0;

    char option; int num;
    while (cin >> option) {
        cin >> num;
        if (option == 'F') {
            x += dx[direction] * num;
            y += dy[direction] * num;
        } else {
            direction += num;
            direction %= 4;
        }
    }

    cout << x << ' ' << y << '\n';
    return 0;
}

