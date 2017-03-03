#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxN = 105, kMod = 1e9+7;
int k;

const int O = 25;

vector<int> vertex[kMaxN];
bool visited[kMaxN];

int dp[kMaxN][50];

void Mod(int& a) {
    if (a >= kMod) {
        a -= kMod;
    }
}

void Solve(int node) {
    visited[node] = true;

    vector<int> children;
    for (auto itr : vertex[node]) {
        if (visited[itr]) {
            continue;
        } else {
            children.push_back(itr);
        }
    }

    // this is black
    int black = 1;
    for (auto itr : children) {
        int a = 0;
        for (int x = O - k + 1; x <= O + k; x += 1) {
            a += dp[itr][a];
        }
        black = (1LL * black * a);
    }

    Mod(dp[node][k + O] += black);
    for (int b = O; b < O + k; b += 1) {
        int num = 0;
        for (auto chosen : children) {
            for (auto child : children) {
                if (child == chosen) {
                    continue;
                }
            }
        }

        Mpd(dp[node][b] += num);
    }
}

int main() {
    int n; cin >> n >> k;
    for (int i = 0; i + 1< n; i += 1) {
        int a, b; cin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    Solve(1);
    return 0;
}
