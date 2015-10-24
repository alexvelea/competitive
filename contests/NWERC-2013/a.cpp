//Problem a @ 03-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <queue>
using namespace std;

const int kMaxN = 2005;
const int inf = 1000000;

#define int64 long long

int father[kMaxN];
vector<pair<int, int> > vertex[kMaxN];
int rez[kMaxN][kMaxN], mat[kMaxN][kMaxN];

int getFather(int nod) {
    if (father[nod] != nod) {
        father[nod] = getFather(father[nod]);
    }
    return father[nod];
}

void unite(int a, int b) {
    if (rand() % 2) {
        swap(a, b);
    }
    a = getFather(a);
    b = getFather(b);
    father[a] = b;
    return ;
}

bool viz[kMaxN];

void df(int start, int nod) {
    viz[nod] = true;
    for (auto itr : vertex[nod]) {
        if (not viz[itr.first]) {
            rez[start][itr.first] = rez[start][nod] + itr.second;
            df(start, itr.first);
        }
    }
}

int main() {
    int n;
    while (cin >> n) {
        vector<tuple<int, int, int> > ev;
        for (int i = 1; i <= n; ++i) {
            vertex[i].clear();
            for (int j = 1; j <= n; ++j) {
                rez[i][j] = 0;
                cin >> mat[i][j];
                ev.push_back(make_tuple(mat[i][j], i, j));
            }
        }

        sort(ev.begin(), ev.end());
        for (int i = 1; i <= n; ++i) {
            father[i] = i;
        }

        vector<tuple<int, int, int> > rezVertex;

        for (auto itr : ev) {
            int cost, a, b;
            tie(cost, a, b) = itr;
            if (getFather(a) != getFather(b)) {
                rez[a][b] = cost;
                vertex[a].push_back(make_pair(b, cost));
                vertex[b].push_back(make_pair(a, cost));
                rezVertex.push_back(make_tuple(a, b, cost));
                unite(a, b);
            }
        }

        int mn = inf;
        int a = 1, b = 2;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                viz[j] = false;
            }

            df(i, i);
            for (int j = 1; j <= n; ++j) {
                if (rez[i][j] != mat[i][j]) {
                    if (mat[i][j] <= mn) {
                        mn = mat[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        rezVertex.push_back(make_tuple(a, b, mn));

        for (auto itr : rezVertex) {
            int cost, a, b;
            tie(a, b, cost) = itr;
            cout << a << ' ' << b << ' ' << cost << '\n';
        }
        cout << '\n';
    }
	return 0;
}
