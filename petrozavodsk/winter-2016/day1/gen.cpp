#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> position = {0};
    cout << 1 << '\n';
    int m = 20;
    cout << m << '\n'; 
    int t = 0;
    for (int i = 0; i < m; i += 1) {
        int bonus = 1 + rand() % max(3, (int)log2(1 + position.back() - position.front()));
        t += bonus;
        vector<int> next = {};
        for (auto itr : position) {
            for (int i = -bonus; i <= bonus; i += 1) {
                next.push_back(i + itr);
            }
        }

        sort(next.begin(), next.end());
        next.resize(unique(next.begin(), next.end()) - next.begin());
        position = next;
        int where = position[rand() % (position.size() - 2)];
        int v = rand () % (int)sqrt(position.back() - position.front());
        cout << t << ' ' << where << ' ' << v + 1 << '\n';

        int l = where - v;
        int r = where + v;
        for (int i = 0; i < (int)position.size(); i += 1) {
            if (l <= position[i] and position[i] <= r) {
                swap(position[i], position.back());
                position.pop_back();
                i -= 1;
            }
        }
    }

    cout << 0 << '\n';
}
