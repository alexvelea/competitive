#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int kMaxN = 3e5+5;
const bool debug = false;

map<pair<int, int>, int> two, one, id;
vector<pair<int, int>> events[kMaxN];

int GetId(int a, int b) {
    if (a > b) {
        swap(a, b);
    }

    if (id[{a, b}] == 0) {
        id[{0, 0}] += 1;
        id[{a, b}] = id[{0, 0}];
    }
    return id[{a, b}];
}

bool used[kMaxN];

int64 OneWayOnly(int id) {
    int64 c = 0;
    for (int i = 0; i < (int)events[id].size(); i += 1) {
        auto& itr = events[id][i];
        if (not used[i]) {
            c += one[{itr.first, itr.second}];
        }
    }
    return c;
}

int64 Solve(int a, int b, int id) {
    if (one[{a, b}] == 0 or (one[{a, b}] > two[{a, b}] and two[{a, b}])) {
        one[{a, b}] = two[{a, b}];
    }

    if (one[{b, a}] == 0 or (one[{b, a}] > two[{b, a}] and two[{b, a}])) {
        one[{b, a}] = two[{b, a}];
    }

    if (two[{a, b}] == 0 and two[{b, a}] == 0) {
        for (int i = 0; i < (int)events[id].size(); i += 1) {
            used[i] = false;
        }
        if (debug) printf("One way:%d %d\n", a, b);
        auto c = OneWayOnly(id);
        if (debug) printf("Cost:%d\n", c);
        return c;
    }

    if (two[{a, b}] == 0) {
        swap(a, b);
    } else if (two[{a, b}] > two[{b, a}] and two[{b, a}] != 0) {
        swap(a, b);
    }

    two[{a, b}] = min(two[{a, b}], one[{a, b}] + one[{b, a}]);
    two[{b, a}] = min(two[{b, a}], one[{a, b}] + one[{b, a}]);

    int ab = one[{a, b}], ba = one[{b, a}], ab2 = two[{a, b}], ba2 = two[{b,a}];

    if (debug) printf("a:%d\tb:%d\tab:%d\tba:%d\tab2:%d\tba2:%d\n", a, b, ab, ba, ab2, ba2);

    int n = (int)events[id].size();
    vector<int> values(n);
    for (int i = 0; i < n; i += 1) {
        used[i] = false;
        if (events[id][i] == make_pair(a, b)) {
            values[i] = 1;
        } else {
            values[i] = -1;
        }
    }

    if (debug) {
        cerr << "Values:\t";
        for (auto itr : values) { cerr << itr << '\t'; }
        cerr << '\n';
    }

    int sum = 0;
    int num_a = 0;

    int64 cost = 0;
    for (auto itr : values) {
        if (itr == +1) {
            cost += ab;
        } else {
            cost += ba;
        }
    }

    // get max num_a
    for (int i = 0; i < n; i += 1) {
        if (values[i] == -1 and sum > 0) {
            num_a += 1;
            cost -= ab + ba;
            cost += ab2;
        }
        sum += values[i];
        if (sum < 0) {
            sum = 0;
        }
    }

    for (int i = 0, c = num_a; i < n and c; i += 1) {
        if (values[i] == +1) {
            c -= 1;
            used[i] = true;
        }
    }

    for (int i = n - 1, c = num_a; i >= 0 and c; i -= 1) {
        if (values[i] == -1) {
            c -= 1;
            used[i] = true;
        }
    }

    if (debug) {
        cerr << "Used:\t";
        for (int i = 0; i < n; i += 1) {
            cerr << used[i] << ' ';
        }
        cerr << '\n';
    }

    if (debug) printf("num_a:%d\t", num_a);

    if (ba2) {
        int sum = 0;
        int num_b = 0;
        for (int i = 0; i < n; i += 1) {
            if (used[i]) {
                continue;
            }
            if (values[i] == +1 and sum < 0) {
                num_b += 1;
                cost -= ab + ba;
                cost += ba2;
            }
            sum += values[i];
            if (sum > 0) {
                sum = 0;
            }
        }
        if (debug) printf("num_b:%d", num_b);
    }
    if (debug) printf("\n");
    if (debug) printf("Cost:%d\n", cost);
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, d; cin >> n >> d;
    vector<int> cities;
    for (int i = 0; i < d; i += 1) {
        int x; cin >> x;
        cities.push_back(x);
    }

    int m; cin >> m;
    while (m--) {
        int a, b; char c; int cost; cin >> a >> b >> c >> cost;
        if (c == 'R') {
            if (two[{a, b}] == 0) {
                two[{a, b}] = cost;
            } else {
                two[{a, b}] = min(two[{a, b}], cost);
            }
        } else {
            if (one[{a, b}] == 0) {

                one[{a, b}] = cost;
            } else {
                one[{a, b}] = min(one[{a, b}], cost);
            }
        }
    }

    for (int i = 0; i + 1 < d; i += 1) {
        events[GetId(cities[i], cities[i + 1])].push_back({cities[i], cities[i + 1]});
    }

    int64 cost = 0;

    for (int i = 1; i <= id[{0, 0}]; i += 1) {
        cost += Solve(events[i][0].first, events[i][0].second, i);
        if (debug) cerr << '\n';
    }

    cout << cost << '\n';
    return 0;
}
