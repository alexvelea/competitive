#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
 
using namespace std;
 
int solve(int node, int from, int to, const vector< vector<int> > &dist, const vector<int> &D, vector< vector< vector<int> > > &dp) {
    if (from == to)
        return 0;
 
    if (dp[node][from][to]  >= 0)
        return dp[node][from][to];
 
    int answer = numeric_limits<int>::max();
    for (int i = from; i < to; ++i)
        answer = min(answer, solve(D[i], from, i, dist, D, dp) + solve(D[i], i + 1, to, dist, D, dp) + dist[node][D[i]]);
    dp[node][from][to] = answer;
    return answer;
}
 
int main() {
    ifstream cin("team.in");
    ofstream cout("team.out");
 
    int P, N, M; cin >> P >> N >> M;
 
    vector< vector<int> > dist(N, vector<int>(N, numeric_limits<int>::max() / 2));
    for (int i = 0; i < N; ++i)
        dist[i][i] = 0;
 
    for (int i = 0; i < M; ++i) {
        int x, y, z; cin >> x >> y >> z;
        --x; --y;
        dist[x][y] = dist[y][x] = min(dist[x][y], z);
    }
 
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
 
    vector<int> D(P);
    for (int i = 0; i < P; ++i) {
        cin >> D[i];
        --D[i];
    }
 
    vector< vector< vector<int> > > dp(N, vector< vector<int> >(P, vector<int>(P, -1)));
    cout << solve(0, 0, P, dist, D, dp) << "\n";
}