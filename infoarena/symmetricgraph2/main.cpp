#include <cassert>

#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int kMaxN = 2e5+5, inf = 0x3f3f3f3f;

typedef long long int64;

vector<pair<int, int>> vertex[kMaxN];

bool is_leaf[kMaxN];
int leaf_index[kMaxN];

int n, m; 


bool visited[kMaxN];
bool color[kMaxN];

vector<int> InitialGraphDf() {
    queue<int> bfs;
    vector<int> leafs;

    visited[1] = visited[n] = true;
    bfs.push(1);
    bfs.push(n);

    color[1] = 0;
    color[n] = 1;

    while (bfs.size()) {
        int nod = bfs.front();
        bfs.pop();

        bool leaf = false;
        int other = -1;

        for (auto edge : vertex[nod]) {
            int& oth = edge.first;
            if (not visited[oth]) {
               visited[oth] = true;
               color[oth] = color[nod];
               bfs.push(oth);
            } else if (color[oth] == color[nod]) {
                // must be father
                continue;
            } else if (color[nod] == 0) {
                other = oth;
                leaf = true;
            }
        }

        if (leaf) {
            leafs.push_back(other);
        }
    }

    for (int i = 1; i <= n; i += 1) {
        visited[i] = false;
    }

    return leafs;
}


bool GraphSort(const pair<int, int>& a, const pair<int, int>& b) {
    return leaf_index[a.first] < leaf_index[b.first];
}   

void SortGraph(int nod) {
    if (is_leaf[nod]) {
        return;
    }

    visited[nod] = true;

    int currect_cost = +inf;

    for (auto edge : vertex[nod]) {
        int& oth = edge.first;
        if (not visited[oth]) {
            SortGraph(oth);
            currect_cost = min(currect_cost, leaf_index[oth]);
        }
    }
    
    leaf_index[nod] = currect_cost;

    sort(vertex[nod].begin(), vertex[nod].end(), GraphSort);
    return;
}

struct DfsInformation {
    DfsInformation(int nod, int64 min_up) 
        : nod(nod), child_iterator(0), min_up(min_up), down_sum(0) { }

    pair<int, int> child() {
        if (child_iterator == (int)vertex[nod].size()) {
            return {-1, -1};
        }

        return vertex[nod][child_iterator++];
    }

    int nod, child_iterator;
    int64 min_up;
    int64 down_sum;
};

struct Dfs {
    Dfs(int start_node) : visited(n+1, false) {
        dfs_stack.reserve(n+1);
        visited[start_node] = true;
        dfs_stack.push_back(DfsInformation(start_node, 1LL * inf * inf));
    }

    vector<bool> visited;
    vector<DfsInformation> dfs_stack;

    void NextChild() {
        if (is_leaf[dfs_stack.back().nod]) {
            PopStack();
        }

        while (1) {
            auto& config = dfs_stack.back();

            if (is_leaf[config.nod]) {
                break;
            }

            auto child = config.child();
            if (child.first == -1) {
                // end of shit.
                PopStack();
                continue;
            }

            if (visited[child.first]) {
                continue;
            }

//            cerr << "[add]" << child.first << '\n';
            visited[child.first] = true;

            dfs_stack.push_back(
                    DfsInformation(
                        child.first, min(1LL * child.second, dfs_stack.back().min_up)));
        }
    }

    void PopStack() {
        auto old_config = dfs_stack.back();
//        cerr << "{delete}" << old_config.nod << '\n';
        dfs_stack.pop_back();
        dfs_stack.back().min_up -= old_config.down_sum;
        dfs_stack.back().down_sum += old_config.down_sum;
    }

    int64 GetMinUp() {
        return dfs_stack.back().min_up;
    }

    void SetFlow(int64 f) {
        dfs_stack.back().down_sum = f;
    }
};

int main() {
    ifstream cin("symmetricgraph2.in");
    ofstream cout("symmetricgraph2.out");
    cin >> n >> m;
    
    for (int i = 1; i <= m; i += 1) {
        int a, b, c; cin >> a >> b >> c;
        vertex[a].push_back({b, c});
        vertex[b].push_back({a, c});
    }

    vector<int> leafs = InitialGraphDf();
    for (int i = 1; i <= n; i += 1) {
        leaf_index[i] = +inf;
    }

    for (int i = 0; i < (int)leafs.size(); i += 1) {
        int itr = leafs[i];
        is_leaf[itr] = true;
        leaf_index[itr] = i;
    }

    SortGraph(1);
    SortGraph(n);

    Dfs source(1), sink(n);
   
    int64 result = 0;
    for (int i = 0; i < (int)leafs.size(); i += 1) {
        source.NextChild();
        sink.NextChild();

//        assert(source.dfs_stack.back().nod == sink.dfs_stack.back().nod);

        int64 f = min(source.GetMinUp(), sink.GetMinUp());
        source.SetFlow(f);
        sink.SetFlow(f);

        result += f;
    }

    cout << result << '\n';

    return 0;
}
