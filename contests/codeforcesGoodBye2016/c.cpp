#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    int min_rating = -inf;
    int max_rating = +inf;
    int n; cin >> n;
    int dif = 0;
    while (n--) {
        int c, dir; cin >> c >> dir;
        if (dir == 1) {
            min_rating = max(min_rating, 1900 - dif);
        } else {
            max_rating = min(max_rating, 1899 - dif);
        }
        dif += c;
    }
    if (max_rating < min_rating) {
        cout << "Impossible";
        return 0;
    }
    if (max_rating > 3e7) {
        cout << "Infinity"; 
        return 0;
    }

    cout << max_rating + dif << '\n';
    return 0;
}
