#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>
using namespace std;

const int kMaxN = 35005;

int v[kMaxN], t[kMaxN];

int Map[105][10500];
vector<tuple<pair<int, int>, int, int> > event[105];
int main() {
    for (int v = 1; v <= 100; ++v) {
        for (int v2 = v + 1; v2 <= 100; ++v2) {
            for (int t = 0; t <= 100; ++t) {
                int difV = v2 -v;
                int a = v * t + t * difV;
                int b = difV;
                int g = __gcd(a, b);
               if (a * v <= 100 * b) {
                    pair<int, int> moment = {a / g, b / g};
                    event[v].push_back(make_tuple(moment, v2, t));
                }
            }
        }
        sort(event[v].begin(), event[v].end());
    }

/*    for (auto itr : event[10]) {
                 pair<int, int> moment;
                int T, v;
                tie(moment, T, v) = itr;
        cerr << moment.first << '\t' << moment.second << '\t' << T << '\t' << v << '\n';    
    }
    
    for (int i = 1; i <= 100; ++i) {
        cerr << event[i].size() << '\n';
    }*/

    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            cin >> t[i] >> v[i];
            Map[v[i]][t[i]]++;
        }

        int mx = 0;

        for (int i = 1; i <= n; ++i) {
            pair<int, int> lastMoment = {-1, -1};
            int init = Map[v[i]][t[i]], nr = init;
            for (auto itr : event[v[i]]) { 
                pair<int, int> moment;
                int T, v;
                tie(moment, v, T) = itr;
                if (moment != lastMoment) {
                    nr = init;;
                }
                lastMoment = moment;
//                cerr << moment.first << '\t' << moment.second << '\t' << v << '\t' << T + t[i] << '\n';
                nr += Map[v][T + t[i]];
                mx = max(mx, nr);
            }
        }

        cout << mx << '\n';
        for (int i = 1; i <= n; ++i) {
            Map[v[i]][t[i]]--;
        }
    }
}
