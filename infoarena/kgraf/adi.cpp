#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int inf = 1000000000;

void dfs(const vector< vector< pair<int, int> > > &E, const int &node, vector<bool> &used, vector<int> &search) {
    if (used[node] == true)
        return;
    
    used[node] = true;
    for (vector< pair<int, int> >::const_iterator it = E[node].begin(); it != E[node].end(); ++it) {
        dfs(E, it -> first, used, search);
    }
    
    search.push_back(node);
}

int main(int argc, char *argv[]) {
    string iname = "kgraf.in";
    string oname = "kgraf.out";
    
    if (argc == 2) {
        iname = oname = argv[1];
        iname += ".in";
        oname += ".ok";
    }
    
    ifstream cin(iname.c_str());
    ofstream cout(oname.c_str());
    
    int N, M, K; cin >> N >> M >> K;
    
    vector< vector< pair<int, int> > > E(N);
    
    for (int i = 0; i < M; ++i) {
        int first, second, distance; cin >> first >> second >> distance;
        --first;
        --second;
        if (first == second)
            continue;
        E[first].push_back(make_pair(second, distance));
    }
    
    vector<int> topological_searching;
    vector<bool> used(N, false);
    for (int i = 0; i < N; ++i)
        dfs(E, i, used, topological_searching);
    
    reverse(topological_searching.begin(), topological_searching.end());
    
    vector< vector<int> > future(N, vector<int>(K + 2, -inf)), present = future;
    for (int i = 0; i < N; ++i)
        future[i][0] = 0;
    
    int answer = -inf;
    for (int i = 0; i <= K; ++i) {
        swap(present, future);
        future = vector< vector<int> >(N, vector<int>(K + 2, -inf));
        for (vector<int>::iterator it = topological_searching.begin(); it != topological_searching.end(); ++it) {
            for (int j = 0; j <= K; ++j) {
                for (vector< pair<int, int> >::iterator jt = E[*it].begin(); jt != E[*it].end(); ++jt) {
                    future[jt -> first][j] = max(future[jt -> first][j], present[*it][j] - jt -> second);
                    present[jt -> first][j + 1] = max(present[jt -> first][j + 1], present[*it][j] + jt -> second);
                    future[jt -> first][j + 1] = max(future[jt -> first][j + 1], present[*it][j]);
                    present[jt -> first][j] = max(present[jt -> first][j], present[*it][j]);
                }
            }
            if (i == K) {
                answer = max(answer, present[*it][K]);
            }
        }
    }
    
    if (answer < 0)
        answer = -1;
    cout << answer << "\n";
}
