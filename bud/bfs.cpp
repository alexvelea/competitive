#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

ifstream fin("data.txt");

vector<int> vertex[100];
int inside[100];
int cost[100];

int main() {
   int n, m; 
   fin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b; 
        fin >> a >> b;
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    queue<int> q;
    q.push(1);
    inside[1] = true;

    while (q.size() > 0) {
        int nod = q.front();
        q.pop();

        for (int i = 0; i < int(vertex[nod].size()); ++i) {
            int other = vertex[nod][i];

            if (!inside[other]) {
                inside[other] = true;
                cost[other] = cost[nod] + 1;
                q.push(other);
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << "Elementul " << i << " are distanta " << cost[i] << '\n';
    }
    return 0;
}
