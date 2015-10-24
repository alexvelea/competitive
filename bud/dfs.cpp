#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream fin("data.txt");

vector<int> vertex[100];
bool viz[100];

void dfs(int nod) {
    cout << "Intra in -> " << nod << '\n';
    viz[nod] = true;

    for (int i = 0; i < int(vertex[nod].size()); ++i) {
        int other = vertex[nod][i];
        if (!viz[other]) {
            dfs(other);
        }
    }
}

int main() {
    int n, m;
    fin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int a, b; 
        fin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    dfs(1);
    return 0;
}
