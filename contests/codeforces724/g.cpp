#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define int64 long long

const int kMaxN = 1e5+5;

struct Edge {
  public:
    int node, index;
    int64 cost;
    
    Edge(int node, int index, int64 cost) 
        : node(node), index(index), cost(cost) { }
};
// Graph edges
vector<Edge> edges[kMaxN];

// Cycle xor values
vector<int64> cycleValues;
// Used to compute the xor on the path from a node to an ancestor.
vector<int64> xorStack;

// Depth of a node in the dfs traversal.
int depth[kMaxN];
bool visited[kMaxN];
vector<int64> depthXor;

// Index of the edge from which a node was expended.
int edgeParent[kMaxN];

void dfs(int node) {
    visited[node] = true;
    
    for (auto& edge : edges[node]) {
        if (edgeParent[node] == edge.index) {
            continue;
        }

        if (visited[edge.node]) {
            // Check if the edge is from a node to a ancester, in this case
            // he'll still be in the stack.
            if (depth[edge.node] > depth[node]) {
                continue;
            }
            
            // The xor of the cycle is the xor of the edge ^ the xor of the
            // edges from node to the ancester(edge.node).
            cycleValues.push_back(xorStack[depth[node]]
                                  ^ xorStack[depth[edge.node]] ^ edge.cost);
        } else {
            depth[edge.node] = depth[node] + 1;
            depthXor.push_back(xorStack.back() ^ edge.cost);
            edgeParent[edge.node] = edge.index;
            
            // Add the new value to the xor stack so the child doesn't need to
            // worry about this.
            xorStack.push_back(xorStack.back() ^ edge.cost);
            dfs(edge.node);
        }
    }
    xorStack.pop_back();
}

int main() {
    int n, m;
    cin >> n >> m;
    
    int sum = 0;
    const int kMod = 1e9+7;
    
    for (int i = 1; i <= m; i += 1) {
        int a, b; int64 cost;
        cin >> a >> b >> cost;
        
        edges[a].push_back(Edge(b, i, cost));
        
        // Don't put double edges.
        if (a != b) {
            edges[b].push_back(Edge(a, i, cost));
        }
    }

    for (int i = 1; i <= n; i += 1) {
        if (visited[i]) {
            continue;
        }

        depthXor.clear();
        cycleValues.clear();

        // Add the xor on stack for the first element (the root)
        xorStack.push_back(0);
        depth[0] = 1;
        dfs(i);

        int64 result = 0;

        // Clasic problem: getting the maximum number which can be obtained by 
        // xoring the values from the vector 'cycleValues'
        vector<int64> selectedNumbers;
        for (int i = 62; i >= 0; i -= 1) {
            bool found = false;
            if (result & (1LL << i)) {
                continue;
            }

            for (auto& itr : cycleValues) {
                if (itr & (1LL << i)) {
                    swap(cycleValues.back(), itr);
                    found = true;
                    break;
                }
            }

            if (not found) {
                continue;
            }

            int64 value = cycleValues.back();
            cycleValues.pop_back();

            for (auto& itr : cycleValues) {
                if (itr & (1LL << i)) {
                    itr ^= value;
                }
            }

            selectedNumbers.push_back(value);
        }

        int64 multiplier = 1LL << ((int64)selectedNumbers.size());
        int64 hMultiplier = 1LL << ((int64)selectedNumbers.size());

        if (selectedNumbers.size() == 0) {
            hMultiplier = 1;
        } else {
            hMultiplier /= 2;
        }


        vector<int> counter[2] = {vector<int>(63, 0), vector<int>(63, 0)};
        depthXor.push_back(0);
        for (auto val : depthXor) {
            for (int j = 0; j < 63; j += 1) {
                counter[!!((1LL << j) & val)][j] += 1;
            }
        }

        int64 cycle_bitmask = 0;
        for (auto itr : selectedNumbers) {
            cycle_bitmask |= itr;
        }

        hMultiplier %= kMod;
        multiplier %= kMod;

        for (auto val : depthXor) {
            for (int j = 0; j < 63; j += 1) {
                if (((1LL << j) & cycle_bitmask)) {
                    sum = (sum + (1LL << j) % kMod * 1LL * hMultiplier % kMod * 1LL * ((int64)depthXor.size() - 1)) % kMod;
                } else {
                    sum = (sum + (1LL << j) % kMod * 1LL * multiplier % kMod * 1LL * counter[!!!((1LL << j) & val)][j]) % kMod;
                }
            }
        }
    }
    cout << (1LL * sum * 500000004) % kMod << '\n';
    return 0;
}

