#include <iostream>
using namespace std;

const int kMaxN = 100, kMaxM = 1000;

int main() {
    int n, m; fin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b; fin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }
    dp[0][1][0] = 1.0;
    for (int time = 1; time <= 
    return 0;
}
