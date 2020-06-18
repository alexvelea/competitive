#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Event {
    int id;
    int time;
    int is_beginning;

    bool operator<(const Event& oth) const {
        return make_pair(time, is_beginning) < make_pair(oth.time, oth.is_beginning);
    }
};

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        int n; cin >> n;

        vector<Event> events;
        vector<int> resposable(n, 0);
        string name = "CJ";
        int available[2] = {1, 1};

        for (int i = 0; i < n; i += 1) {
            int a, b; cin >> a >> b;
            events.push_back({i, a, true});
            events.push_back({i, b, false});
        }

        bool ok = true;
        sort(events.begin(), events.end());

        for (auto& itr : events) {
            if (itr.is_beginning) {
                int person = -1;
                if (available[0]) { person = 0; }
                if (available[1]) { person = 1; }
                if (person == -1) {
                    ok = false;
                } else {
                    available[person] = false;
                    resposable[itr.id] = person;
                }
            } else {
                available[resposable[itr.id]] = true;
            }
        }

        cout << "Case #" << t << ": ";
        if (ok) {
            for (int i = 0; i < n; i += 1) { cout << name[resposable[i]]; }
        } else {
            cout << "IMPOSSIBLE";
        }

        cout << '\n';
    }
}
