#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

ifstream fin("sortop.in");
ofstream fout("sortop.out");

const int kMaxN = 1e5+5;

bool visited[kMaxN];

vector<int> vertex[kMaxN];
int parent[kMaxN];

unordered_map<int, bool> is_parent[kMaxN];
vector<int> parent_events[kMaxN];
bool in_stack[kMaxN];

void df(int nod) {
    visited[nod] = true;
    in_stack[nod] = true;
    for (int i = 0; i < int(vertex[nod].size()); i += 1) {
        int oth = vertex[nod][i];
        if (visited[oth]) {
            parent[nod] = oth;
            vertex[nod][i] = vertex[nod].back();
            vertex[nod].pop_back();
        } else {
            df(oth);
        }
    }

    for (auto itr : parent_events[nod]) {
        if (in_stack[itr]) {
            is_parent[nod][itr] = true;
        }
    }

    in_stack[nod] = false;
}

int main() {
    int n, k; fin >> n >> k;
    for (int i = 1; i < n; i += 1) {
        fin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    for (int i = 1; i <= k; i += 1) {
        int nod, color; fin >> nod >> color;
        selected[nod] = true;
        value[nod] = color;
        events.push_back({color, nod});
    }

    sort(events.begin(), events.end());
    df(1);
}
