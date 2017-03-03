#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;

int h, max_node;

vector<int> cached[200];
bool visited[200];

vector<int> Query(int node) {
    if (visited[node]) {
        return cached[node];
    }
    cout << "? " << node << endl;
    int x; cin >> x;
    vector<int> p;
    while (x--) {
        int a; cin >> a;
        p.push_back(a);
    }
    cached[node] = p;
    return p;
}

void Set(int node) {
    cout << "! " << node << endl;
}

bool IsLeaf(int node) {
    return Query(node).size() == 1;
}

bool Terminal(int node) {
    return Query(node).size() == 2;
}

int GetLeaf() {
    while (1) {
        int x = rand() % (max_node - 1) + 1;
        if (IsLeaf(x)) {
            return x;
        }
    }
}

vector<int> GetUnvisited(int node) {
    auto nearby = Query(node);
    for (int i = 0; i < (int)nearby.size(); i += 1) {
        if (visited[nearby[i]]) {
            swap(nearby[i], nearby.back());
            nearby.pop_back();
            i -= 1;
        }
    }
    return nearby;
}


bool finished = false;

vector<int> GoUp(int node, int dist) {
    vector<int> history = {};
    int num_steps = 0;
    while (dist--) {
        history.push_back(node);
        auto nearby = Query(node);
        num_steps += 1;

        if (IsLeaf(node)) {
            return history;
        }

        if (Terminal(node)) {
            Set(node);
            finished = true;
            return history;
        }

        auto unvisited = GetUnvisited(node);
        node = unvisited[rand() % unvisited.size()];
    }

    return history;
}

void Solve() {
    int leaf = GetLeaf();

    auto history = GoUp(leaf, h);
    int height = 0;
    if (finished) {
        return;
    }

    int s = history.size();
    if (IsLeaf(history.back())) {
        int mid = history[s / 2];
        int father = GetUnvisited(mid)[0];
        if (Terminal(father)) {
            Set(father);
            return;
        }
        height = s / 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    while (cin >> h) {
        finished = false;
        int max_node = (1 << h) - 1;
        for (int i = 1; i <= max_node; i += 1) {
            visited[i] = false;
        }

        if (h == 0) {
            exit(0);
        }

        if (h <= 4) {
            for (int i = 1; ; i += 1) {
                auto x = Query(i);
                if (x.size() == 2) {
                    Set(i);
                }
                break;
            }
            continue;
        }

        if (h == 5) {
            Solve5();
        } else if (h == 6) {
            Solve6();
        } else if (h == 7) {
            Solve7();
        }
    }
    return 0;
}
