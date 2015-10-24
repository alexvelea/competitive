//Problem h @ 14-10-2015
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 605;

#define int64 long long

map<pair<int, int>, int> segmentId;
map<pair<int, int>, int> nodeId;
int numberOfNodes = 0;

pair<int, int> coord[kMaxN], point[2];
pair<int, int> father[kMaxN][4];
int djk[kMaxN][4];

int getNodeId(int a, int b) {
    if (nodeId[make_pair(a, b)] == 0) {
        nodeId[make_pair(a, b)] = ++numberOfNodes;
        coord[numberOfNodes] = make_pair(a, b);
    }
    return nodeId[make_pair(a, b)];
}

int getNodeId(pair<int, int> a) {
    return getNodeId(a.first, a.second);
}                    

vector<pair<int, int> > vertex[kMaxN];

bool isUp(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    if (a.first == b.first) {
        return false;
    }

    if (a.first > b.first) {
        swap(a, b);
    }

    if (a.first <= c.first and c.first < b.first) {
        return ((a.first - c.first) * (a.second - b.second) + (c.second - a.second) * (a.first - b.first) <= 0);
    } else {
        return false;
    }
}

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x1, y1, x2, y2, v; cin >> x1 >> y1 >> x2 >> y2 >> v;
        segmentId[make_pair(getNodeId(x1, y1), getNodeId(x2, y2))] = i;
        segmentId[make_pair(getNodeId(x2, y2), getNodeId(x1, y1))] = i;

        vertex[getNodeId(x1, y1)].push_back(make_pair(getNodeId(x2, y2), v));
        vertex[getNodeId(x2, y2)].push_back(make_pair(getNodeId(x1, y1), v));
    }

    for (int i = 0; i < 2; ++i) {
        cin >> point[i].first >> point[i].second;
    }
    int mx = inf;
    vector<int> rez;
 
    for (int start = 1; start <= numberOfNodes; ++start) {
    
	for (int i = 1; i <= numberOfNodes; ++i) {
        djk[i][0] = inf;
        djk[i][1] = inf;
        djk[i][2] = inf;
        djk[i][3] = inf;
    }
    djk[start][0] = 0;
    father[start][0] = {0, 0};

    priority_queue<pair<int, pair<int, int> > > pq;
    pq.push(make_pair(0, make_pair(start, 0)));

    while (pq.size()) {
        int config = pq.top().second.second;
        int nod = pq.top().second.first;
        int cost = -pq.top().first;
        pq.pop();
        
        if (cost != djk[nod][config]) {
            continue;
        }
    
        for (auto itr : vertex[nod]) {
            int _config = config;
            _config ^= isUp(coord[nod], coord[itr.first], point[0]);
            _config ^= 2 * isUp(coord[nod], coord[itr.first], point[1]);
            int _cost = djk[nod][config] + itr.second;
            if (djk[itr.first][_config] > _cost) {
                djk[itr.first][_config] = _cost;
                father[itr.first][_config] = make_pair(nod, config);
                pq.push(make_pair(-_cost, make_pair(itr.first, _config)));
            }
        }
    }
    if (djk[start][1] < mx) {
        mx = djk[start][1];
        rez.clear();
        for (int nod = start, config = 1; not(nod == 0 and config == 0); ) {
            rez.push_back(nod);
            int _nod, _config;
            _nod = father[nod][config].first;
            _config = father[nod][config].second;
            nod = _nod;
            config = _config;
        }
    }

    if (djk[start][2] < mx) {
        mx = djk[start][2];
        rez.clear();
        for (int nod = start, config = 2; not(nod == 0 and config == 0); ) {
            rez.push_back(nod);
            int _nod, _config;
            _nod = father[nod][config].first;
            _config = father[nod][config].second;
            nod = _nod;
            config = _config;
        }
    } 
    }

    cout << mx << '\n';
    cout << rez.size() - 1 << '\n';
    for (int i = 0; i + 1 < int(rez.size()); ++i) {
        cout << segmentId[make_pair(rez[i], rez[i + 1])] << ' ';
    }
    return 0;
}
