#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long
const int kMaxN = 3e5+5;
const int inf = 0x3f3f3f3f;

ifstream fin("avioane2.in");
ofstream fout("avioane2.out");

struct Edge {
    int a, b, x, y, cost;
    Edge(int a, int b, int x, int y, int p) {
        this->a = a;
        this->b = b;
        this->x = x;
        this->y = y;
        this->cost = p;
    }
};

vector<Edge> edge;
vector<pair<int, int> > vertex[kMaxN];
vector<int> node_id[kMaxN], times[kMaxN];
int best_djk[kMaxN];

int node_cnt = 0;

int get_node(int node, int time) {
    int itr = lower_bound(times[node].begin(), times[node].end(), time) - times[node].begin(); 
    if (times[node][itr] > time) {
        itr--;
    }
    return node_id[node][itr];
}

int main() {
    int n, m, q; fin >> n >> m >> q;
    edge.reserve(m);
    for (int i = 0; i < m; i += 1) {
        int a, x, b, y, p; fin >> a >> x >> b >> y >> p;
        a -= 1;
        b -= 1;
        times[a].push_back(x);
        times[b].push_back(y);

        edge.push_back(Edge(a, b, x, y, p));
    }

    for (int i = 0; i < n; i += 1) {
        times[i].push_back(0);
        times[i].push_back(+inf);
        sort(times[i].begin(), times[i].end());
        times[i].resize(unique(times[i].begin(), times[i].end()) - times[i].begin());
        for (int itr = 0; itr < int(times[i].size()); itr += 1) {
            if (itr != 0) {
                vertex[node_cnt - 1].push_back({node_cnt, 0});
            } 
            node_id[i].push_back(node_cnt++);
        }
    }

    for (auto itr : edge) {
        vertex[get_node(itr.a, itr.x)].push_back({get_node(itr.b, itr.y), itr.cost});    
    }

    for (int i = 0; i < node_cnt; i += 1) {
        best_djk[i] = +inf;
    }
    best_djk[get_node(0, 0)] = 0;
    priority_queue<pair<int, int> > pq;
    pq.push({0, get_node(0, 0)});

    while(pq.size()) {
        int cost, node;
        tie(cost, node) = pq.top();
        cost *= -1;
        pq.pop();

        if (cost > best_djk[node]) {
            continue;
        }

        for (auto itr : vertex[node]) {
            if (best_djk[itr.first] > itr.second + best_djk[node]) {
                best_djk[itr.first] = itr.second + best_djk[node];
                pq.push({-best_djk[itr.first], itr.first});
            }
        }
    }

    for (int i = 0; i < q; i += 1) {
        int target, time; fin >> target >> time;
        target -= 1;
        int id = get_node(target, time);
        fout << ((best_djk[id] == inf) ? (-1) : (best_djk[id])) << '\n';
    }
    return 0;
}
