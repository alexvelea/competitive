#include <cassert>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 2e5+5;

vector<int> vertex[kMaxN];

int parent[kMaxN];
bool visited[kMaxN];

void Root(int node) {
    visited[node] = true;
    for (int i = 0; i <(int)vertex[node].size(); i += 1) {
        int oth = vertex[node][i];
        if (visited[oth]) {
            vertex[node][i] = vertex[node].back();
            vertex[node].pop_back();
            i -= 1;
        } else {
            parent[oth] = node;
            Root(oth);
        }
    }
    visited[node] = false;
}

int path[kMaxN];

void ClearPaths(int node) {
    sort(vertex[node].begin(), vertex[node].end(), [&](int a, int b) { return path[a] < path[b]; });
    
    int last_path = 0;
    vector<int> remaining;
    for (int i = 0; i < (int)vertex[node].size(); i += 1) {
        int a = vertex[node][i]; 
        if (path[a] == last_path and last_path != 0) {
        } else {
            remaining.push_back(a);
            last_path = path[a];
        }
    }

    vertex[node] = remaining;

}

void ComputePaths(int node) {
    for (auto itr : vertex[node]) {
        ComputePaths(itr);
    }

    ClearPaths(node);

    if (vertex[node].size() == 0) {
        path[node] = 1;

        return;
    } else if (vertex[node].size() == 1) {
        if (path[vertex[node][0]]) {
            path[node] = 1 + path[vertex[node][0]];
        }

        return;
    } else {
        path[node] = 0;
    }
}

void Fail() {
    cout << "-1\n";
    exit(0);
}

void Answer(int val) {
    while (val > 0 and val % 2 == 0) {
        val /= 2;
    }

    cout << val << '\n';
    exit(0);
}

void GoRootDown(int node) {
    ClearPaths(node);
    int num_bad = 0;
    for (auto itr : vertex[node]) {
        num_bad += (path[itr] == 0); 
    }

    if (num_bad > 1) {
        Answer(-1);
    } else if (num_bad == 0) {
        if (vertex[node].size() == 0) {
            Answer(0);
        }

        if (vertex[node].size() == 1) {
            Answer(path[vertex[node][0]]);
        }
        if (vertex[node].size() == 2) {
            Answer(path[vertex[node][0]] + path[vertex[node][1]]);
        }

        Answer(-1);
    }
    
    if (vertex[node].size() == 1) {
        path[node] = 1;
        vertex[vertex[node][0]].push_back(node);
        assert(path[vertex[node][0]] == 0);
        GoRootDown(vertex[node][0]);
    } else if (vertex[node].size() == 2) {
        path[node] = 1 + path[vertex[node][1]];
        vertex[vertex[node][0]].push_back(node);
        assert(path[vertex[node][0]] == 0);
        GoRootDown(vertex[node][0]);       
    } else {
        Answer(-1);
    }

    assert(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i + 1 < n; i += 1) {
        int a, b; cin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    Root(1);
    ComputePaths(1);
    GoRootDown(1);
    return 0;
}
