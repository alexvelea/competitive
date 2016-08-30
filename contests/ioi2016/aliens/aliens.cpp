#include "aliens.h"

#include <vector>
using namespace std;

typedef long long int64;

int64 take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
    vector<pair<int, int>> events;
    for (int i = 0; i < n; i += 1) {
        if (r[i] > c[i]) {
            swap(r[i], c[i]);
        }

        events.push_back({r[i], c[i]});
    }

    sort(events.begin(), events.end(), [](pair<int, int> a, pair<int, int> b) {
            return make_pair(a.first, -a.second) < make_pair(b.first, -b.second);        
        });

    int max_c = 0;
    vector<pair<int, int>> final_events;
 
    for (auto itr : events) {
        if (itr.second <= max_c) {
            continue;
        }

        final_events.push_back(itr);
    }

    int64 cost = 0;

    return 0;
}
