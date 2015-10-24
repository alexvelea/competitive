//Problem g @ 26-09-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;

#define int64 long long

int main() {
	ios::sync_with_stdio(false);
    ifstream fin("pulp.in");
    ofstream fout("pulp.out");
    int n; fin >> n;
    vector<pair<int64, int64> > event;
    for (int i = 1; i <= n; ++i) {
        int start, d; fin >> start >> d;
        event.push_back(make_pair(start, d));
    }
    sort(event.begin(), event.end());
    event.push_back(make_pair(1LL * inf * inf, -1));

    int64 rez = 0, t = 0;

    priority_queue<int64> pq;

    for (int i = 0; i < n or pq.size(); ) {
        int64 active = 1LL * inf * inf;
        if (pq.size()) {
            active = -pq.top();
            pq.pop();
        }

        int64 nextTime = min(active + t, event[i].first);
        while (event[i].first == nextTime and i < n) {
            pq.push(-event[i].second);
            ++i;
        }

//        cerr << t << '\t' << nextTime << '\t' << i << '\t' << active << '\n';

        if (active != 1LL * inf * inf) {
            if (active <= nextTime - t) {
                rez += t + active;
//                cerr << t << '\t' << active << '\n';
            } else {
                active -= nextTime - t;
                pq.push(-active);
            }
        }
        t = nextTime;
    }

//    rez -= 1LL * inf * inf;
    fout << rez << '\n';
	return 0;
}
