#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("drumuri5.in");
ofstream fout("drumuri2.out");

const int MAX_N = 150100;
const int MAX_M = 300100;

typedef vector<vector<int> > Graph;

int N, M;
int NN;
Graph ig, tig; //initial graph and transposed
Graph ng; //new graph
vector<vector<int> > sccs;
vector<int> in_scc;
vector<int> grd;
vector<int> ans;

void readfin();
void printfout();
void solve();
void kosaraju();
void dfs(int node, const Graph &g, vector<bool> &vis, vector<int> &st);
void add_node(int node);

int main() {
    readfin();
    solve();
    printfout();
    return 0;
}

void readfin() {
    fin >> N >> M;
    
    ig.resize(N + 1);
    tig.resize(N + 1);
    for (int i = 1, a, b; i <= M; i += 1) {
        fin >> a >> b;
        ig[a].push_back(b);
        tig[b].push_back(a);
    }
}

void solve() {
    kosaraju();
    
    ng.resize(NN);
    grd.resize(NN);
    for (int i = 0; i < NN; i += 1) {
        for (int j = 0; j < int(sccs[i].size()); j += 1) {
            int node = sccs[i][j];
            for (int k = 0; k < int(ig[node].size()); k += 1) {
                int next = ig[node][k];
                if (in_scc[next] == i) continue;
                ng[i].push_back(in_scc[next]);
                grd[in_scc[next]] += 1;
            }
        }
    }
    
    queue<int> q;
    for (int i = 0; i < NN; i += 1)
        if (grd[i] == 0)
            q.push(i);
    
    vector<int> dset;
    while (not q.empty()) {
        while (not q.empty()) {
            dset.push_back(q.front());
            q.pop();
        }
        
        for (int i = 0; i < int(dset.size()); i += 1) {
            int node = dset[i];
            for (int j = 0; j < int(ng[node].size()); j += 1)
                if (--grd[ng[node][j]] == 0) {
                    q.push(ng[node][j]);
                }
        }
        if (dset.size() == 1) add_node(dset[0]);
        
        dset.clear();
    }
    
    sort(ans.begin(), ans.end());
}

inline void add_node(int node) {
    for (int i = 0; i < int(sccs[node].size()); i += 1) {
        ans.push_back(sccs[node][i]);
    }
}

void kosaraju() {
    vector<bool> visited(N + 1, 0);
    vector<int> st;
    
    for (int i = 1; i <= N; i += 1)
        if (not visited[i])
            dfs(i, ig, visited, st);
    
    fill(visited.begin(), visited.end(), 0);
    in_scc.resize(N + 1);
    NN = 0;
    
    while (not st.empty()) {
        int node = st.back();
        st.pop_back();
        
        if (visited[node]) continue;
        
        sccs.push_back(vector<int>());
        dfs(node, tig, visited, sccs.back());
        
        for (int i = 0; i < int(sccs[NN].size()); i += 1) {
            in_scc[sccs[NN][i]] = NN;
        }
        NN += 1;
    }
}

void dfs(int node, const Graph &g, vector<bool> &vis, vector<int> &st) {
    vis[node] = true;
    
    for (int i = 0; i < int(g[node].size()); i += 1)
        if (not vis[g[node][i]])
            dfs(g[node][i], g, vis, st);
    
    st.push_back(node);
}

void printfout() {
    fout << ans.size() << '\n';
    for (int i = 0; i < int(ans.size()); i += 1) {
        fout << ans[i] << ' ';
    }
}
