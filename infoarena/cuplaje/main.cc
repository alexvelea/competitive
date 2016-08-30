#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

ifstream fin("cuplaje.in");
ofstream fout("cuplaje.out");

const int kMaxN = 2e5+5;
int boy[kMaxN];

set<int> grills;

int main() {
    int n, m; fin >> n >> m;
    for (int i = 1; i <= n; i += 1) {
        fin >> boy[i];
    }
    
    vector<pair<int, int> > grill_events;
    for (int i = 1; i <= m; i += 1) {
        int grill; fin >> grill;
        grill_events.push_back({grill, i});
    }
    sort(grill_events.begin(), grill_events.end());
    int count = 0;
    for (int i = n; i >= 1; i -= 1) {
        while (grill_events.size() and grill_events.back().first >= i) {
            grills.insert(grill_events.back().second);
            grill_events.pop_back();
        }

        if (not grills.empty()) {
            auto itr = grills.lower_bound(boy[i] + 1);
            if (itr != grills.begin()) {
                itr--;
                assert(*itr <= boy[i]);
                count += 1;
                grills.erase(itr);
            }
        }
    }

    fout << count << '\n';
}

