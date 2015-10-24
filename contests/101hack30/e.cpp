//Problem e @ 21-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 6e3 + 5, kMod[2] = {1e9 + 9, 666013};;
const double eps = 1e-7;

#define int64 long long

int cost[kMaxN];
char charElement[kMaxN];
    
vector<pair<int, int> > vertex[kMaxN];
int E9 = 1e9;
int nrOfKeys = 0;

unordered_map<int, int> best[kMaxN];

int nrOfAp[kMaxN * kMaxN / 10];

int getCharId(char c) {
    int64 key = 1LL * E9 * (c - 'a' + 1) + (c - 'a' + 1);
    if (used[key] == 0) {
        used[key] = ++nrOfKeys;
        id = used[key];
    } else {
        id = used[key];
    }          
}

int main() {
	ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b >> cost[i] >> charElement[i];
        vertex[a].push_back(make_pair(b, i));
        vertex[b].push_back(make_pair(a, i));
    }
    cin >> txt;
    int n = int(txt.size());

    for (int st = 0; st < n; ++st) {
        vector<int> rez = {0, 0};
        for (int dr = st; dr < n; ++dr) {
            for (int i = 0; i < 2; ++i) {
                rez[i] = (1LL * rez[i] * 27 + (txt[dr] - 'a' + 1)) % kMod[i];
            }
            int64 key = 1LL * rez[0] * E9 + rez[1];
            int id;
            if (used[key] == 0) {
                used[key] = ++nrOfKeys;
                id = used[key];
            } else {
                id = used[key];
            }
            rez[st][dr] = id;
            nrOfAp[id] += 1;
        }
    }

    for (int i = 0; i < 26; ++i) {
        int id = getCharId(char('a' + i));
        charId[i] = id;
    }

    priority_queue<pair<int, pair<int, int> > > pq;

    for (auto itr : vertex[1]) {
        int id = charId[charElement[itr.second]];
        if (nrOfAp[id] != 0) {
            best[itr.first][id] = cost[itr.second] * nrOfAp[id]; 
            pq.push(make_pair(-cost[itr.second] * nrOfAp[id], make_pair(itr.first, id)));
        }
    }

    while (pq.size()) {
        int nod, cost, id;
        cost = -pq.top().first;
        nod = pq.top().second.first;
        id = pq.top().second.second;
        if (cost != best[nod][id]) {
            continue; 
        }

        for (auto itr : vertex[nod]) {
        }
    }
	return 0;
}
