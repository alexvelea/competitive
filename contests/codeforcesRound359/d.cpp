#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 3e5+5;

vector<int> vertex[kMaxN];
vector<pair<int, int>> queries_here[kMaxN];
int answer[kMaxN];

int depth[kMaxN];

struct DownDp {
    int root;
    int max_path_len, path_node;
    
    int diameter_lca;
    int diameter_len;
    int diameter_vertex[2];

    DownDp() = default;

    DownDp(int n) : root(n), max_path_len(0), path_node(n), diameter_lca(n),  diameter_len(0) {
        diameter_vertex[0] = n;
        diameter_vertex[1] = n;
    }

    void Merge(DownDp oth) {
        oth.max_path_len += 1;

        if (oth.max_path_len + max_path_len > diameter_len) {
            diameter_len = oth.max_path_len + max_path_len;
            diameter_lca = root;
            diameter_vertex[0] = oth.path_node;
            diameter_vertex[1] = path_node;
        }

        if (oth.max_path_len > max_path_len) {
            max_path_len = oth.max_path_len;
            path_node = oth.path_node;
        }

        if (oth.diameter_len > diameter_len) {
            diameter_len = oth.diameter_len;
            diameter_lca = oth.diameter_lca;
            diameter_vertex[0] = oth.diameter_vertex[0];
            diameter_vertex[1] = oth.diameter_vertex[1];
        }
    }
} result[kMaxN];

void Solve(int nod) {
    result[nod] = DownDp(nod);
    for (auto itr : vertex[nod]) {
        depth[itr] = depth[nod] + 1;
        Solve(itr);
        result[nod].Merge(result[itr]);
    }

    int x = result[nod].diameter_len / 2;
    if (x * 2 == result[nod].diameter_len) {
        if (depth[result[nod].diameter_vertex[0]] - depth[result[nod].diameter_lca] >= x) {
            queries_here[result[nod].diameter_vertex[0]].push_back({nod, x});
        } else {
            queries_here[result[nod].diameter_vertex[1]].push_back({nod, x});
        }
    } else {
        x += 1;
        if (depth[result[nod].diameter_vertex[0]] - depth[result[nod].diameter_lca] >= x) {
            queries_here[result[nod].diameter_vertex[0]].push_back({nod, x});
        } else {
            queries_here[result[nod].diameter_vertex[1]].push_back({nod, x});
        }      
    }
}


vector<int> st;
void SolveQueries(int nod) {
    st.push_back(nod);
    for (auto itr : vertex[nod]) {
        SolveQueries(itr);
    }

    for (auto itr : queries_here[nod]) {
        answer[itr.first] = st[depth[nod] - itr.second];
    }
    st.pop_back();
}
int main() {
    ios_base::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    for (int i = 2; i <= n; i += 1) {
        int x; cin >> x;
        vertex[x].push_back(i);
    }

    Solve(1);
    SolveQueries(1);

    for (int i = 1; i <= q; i += 1) {
        int x; cin >> x;
        cout << answer[x] << '\n';
    }

    return 0;
}
