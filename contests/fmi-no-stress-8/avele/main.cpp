#include <fstream>
#include <iostream>
using namespace std;

typedef long long int64;

const int kMaxN = 1e5+5, kMaxDepth = 75;
int64 add_cost, remove_cost;

struct CostHistory {
    int64 cost;
    int64 num_add, num_remove;

    CostHistory operator+(const CostHistory& rhs) const {
        CostHistory ans;
        ans.cost = cost + rhs.cost;
        ans.num_add = num_add + rhs.num_add;
        ans.num_remove = num_remove + rhs.num_remove;
        return ans;
    }

    bool operator<(const CostHistory& rhs) const {
        return cost < rhs.cost;
    }
};


CostHistory empty_cost[kMaxDepth];

struct Node {
    int left, right;
    int subtree_size;
    CostHistory best_cost[kMaxDepth];
} nodes[kMaxN];

void Solve(int id) {
    auto& node = nodes[id];

    CostHistory depth_cost[2][kMaxDepth];
    bool k = false;

    for (auto oth : {node.left, node.right}) {
        if (oth) {
            Solve(oth);
            node.subtree_size += nodes[oth].subtree_size;
            for (int i = 0; i < kMaxDepth; i += 1) {
                depth_cost[k][i] = nodes[oth].best_cost[i];
            }
        } else {
            for (int i = 0; i < kMaxDepth; i += 1) {
                depth_cost[k][i] = empty_cost[i];
            }
        }

        k ^= 1;
    }

    node.subtree_size += 1;
    node.best_cost[0] = {node.subtree_size * remove_cost, 0, node.subtree_size};
    node.best_cost[1] = {(node.subtree_size - 1) * remove_cost, 0, node.subtree_size - 1};

    for (int i = 2; i < kMaxDepth; i += 1) {
        node.best_cost[i] = {(int64)1e18, 0, 0};

        node.best_cost[i] = min(node.best_cost[i], depth_cost[0][i - 1] + depth_cost[1][i - 1]);
        node.best_cost[i] = min(node.best_cost[i], depth_cost[0][i - 1] + depth_cost[1][i - 2]);
        node.best_cost[i] = min(node.best_cost[i], depth_cost[0][i - 2] + depth_cost[1][i - 1]);
    }
}

int main() {
    ifstream cin("avele.in");
    ofstream cout("avele.out");

    int n; cin >> n;
    cin >> add_cost >> remove_cost;
    for (int i = 0; i < n; i += 1) {
        cin >> nodes[i + 1].left >> nodes[i + 1].right;
    }

    empty_cost[0] = {0, 0, 0};
    empty_cost[1] = {add_cost, 1, 0};
    for (int i = 2; i < kMaxDepth; i += 1) {
        empty_cost[i] = empty_cost[i - 1] + empty_cost[i - 2];
        empty_cost[i].cost += add_cost;
        empty_cost[i].num_add += 1;
    }

    Solve(1);

    CostHistory mn = nodes[1].best_cost[1];
    int where = 1;
    for (int i = 2; i < kMaxDepth; i += 1) {
        if (nodes[1].best_cost[i].cost < mn.cost) {
            where = i;
        }
        mn = min(mn, nodes[1].best_cost[i]);
    }

    cout << mn.cost << '\n';
    cerr << mn.num_add << '\t' << mn.num_remove << '\n';
    cerr << where << '\n';
}
