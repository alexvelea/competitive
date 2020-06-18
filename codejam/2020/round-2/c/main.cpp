#include <sys/time.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

const int kMaxN = 105;
typedef long long int64;

struct Point {
    int id;
    int x, y;

    pair<int, int> Slope(const Point& rhs) const {
        int a = rhs.x - x;
        int b = rhs.y - y;
        auto d = abs(__gcd(a, b));
        return {a / d, b / d};
    }

    double Distance(const Point& rhs) const {
        return sqrt(
                1LL * (x - rhs.x) * (x - rhs.x) + 
                1LL * (y - rhs.y) * (y - rhs.y)
        );
    }

    bool operator<(const Point& rhs) const {
        if (x == rhs.x) {
            return y < rhs.y;
        }
        return x < rhs.x;
    }
};

int n;
vector<Point> points;

map<pair<int, int>, int> slopes[kMaxN];
map<pair<int, int>, int> possible_slopes;

void Init() {
    possible_slopes.clear();

    for (int i = 0; i < n; i += 1) {
        slopes[i].clear();
        auto o = points[i];
        for (auto oth : points) {
            if (oth.id == i) { continue; }
            auto slope = o.Slope(oth);
            if (slope.first < 0) { continue; }
            if (slope.first == 0 and slope.second == -1) { continue; }

            if (slopes[i].count(slope)) {
                auto current = points[slopes[i][slope]];
                if (o.Distance(current) > o.Distance(oth)) {
                    slopes[i][slope] = oth.id;
                }
            } else {
                slopes[i][slope] = oth.id;
            }

            possible_slopes[slope] = true;
        }
    }
}

int mx = 0;
void SolveSlope(pair<int, int> slope) {
    vector<int> next_point(n, -1),  prev_point(n, -1);
    for (auto& itr : points) {
        auto p_id = slopes[itr.id].find(slope);
        if (p_id == slopes[itr.id].end()) { continue; }
        
        int id = (*p_id).second;
        next_point[itr.id] = id;
        prev_point[id] = itr.id;
    }

    vector<int> inside_chain(n);
    for (auto& itr : points) {
        inside_chain[itr.id] += 1;
        if (prev_point[itr.id] != -1) {
            inside_chain[prev_point[itr.id]] = inside_chain[itr.id];
        }
    }

    int sum = 0;
    int num_odd = 0;
    int one = 0;
    for (auto& itr : points) {
        if (prev_point[itr.id] == -1) {
            int inside = inside_chain[itr.id];
            if (inside == 1) {
                one += 1;
            } else {
                sum += inside;
                num_odd += inside % 2;
            }
        }
    }

    if (num_odd % 2 == 0) {
        sum += min(2, one);
    } else {
        sum += min(1, one);
    }

    mx = max(mx, sum);
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        cin >> n;
        points.resize(n);
        for (int i = 0; i < n; i += 1) {
            points[i].id = i;
            cin >> points[i].x >> points[i].y;
        }

        Init();
        sort(points.begin(), points.end());
        reverse(points.begin(), points.end());

        mx = 1;
        for (auto& itr : possible_slopes) {
            SolveSlope(itr.first);
        }

        cout << "Case #" << t << ": " << min(n, mx) << '\n';
    }

    return 0;
}
