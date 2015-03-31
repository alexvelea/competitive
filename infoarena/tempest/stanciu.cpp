#include <fstream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <cassert>
 
#define pe pair<long long, int>
#define mp make_pair
#define fi first
#define se second
 
using namespace std;
 
ifstream fin("tempest.in");
ofstream fout("tempest.out");
 
const int MAX_N = 500100;
const long long INF = ((long long)1 << 60);
 
vector<pe> A[MAX_N];
 
vector<long long> mu;
 
long long d[MAX_N];
bool viz[MAX_N];
int n, m;
 
vector<int> sol;
 
class cmp {
public:
    inline bool operator()(const pe &a, const pe &b) {
        return a.fi > b.fi;
    }
};
 
priority_queue<pe, vector<pe>, cmp> Q;
 
void dijkstra(int s) {
    for(int i = 1; i <= n; i++) {
        d[i] = INF;
        viz[i] = false;
    }
 
    d[s] = 0;
    Q.push(mp(0, s));
     
    while(!Q.empty()) {
        int nod = Q.top().se;
        Q.pop();
        if(viz[nod]) {
            continue;
        }
        viz[nod] = true;
        for(auto it : A[nod]) {
            if(d[nod] + it.fi < d[it.se]) {
                d[it.se] = d[nod] + it.fi;
                Q.push(mp(d[it.se], it.se));
            }
        }
    }
}
 
void solve() {
    int S, D;
    fin >> n >> m >> S >> D;
    mu.clear();
    for(int i = 1; i <= n; i++) {
        A[i].clear();
    }
    for(int i = 1; i <= m; i++) {
        int a, b;
        long long c;
        fin >> a >> b >> c;
        A[a].push_back(mp(c, b));
        A[b].push_back(mp(c, a));
        mu.push_back(c);
    }
 
    int k;
    fin >> k;
 
    long long cost = 0;
    for(int i = 1; i <= k; i++) {
        int x;
        fin >> x;
        cost += mu[x - 1];
    }
 
 
    dijkstra(D);
     
    sol.clear();
    for(int i = 1; i <= n; i++) {
        if(d[i] <= cost) {
            sol.push_back(i);
        }
    }
    fout << sol.size() << '\n';
    for(auto it : sol) {
        fout << it << ' ';
    }
    fout << '\n';
}
 
int main() {
    int t;
    fin >> t;
    for(int i = 1; i <= t; i++) {
        solve();
    }
 
    return 0;
}
