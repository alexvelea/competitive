//Problem team2 @ 17-06-2015
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 505, kMaxP = 55;

#define int64 long long

ifstream fin("team.in");
ofstream fout("team.out");

bool viz[kMaxN];
int Distance[kMaxN][kMaxN];
int destination[kMaxP];
int best[kMaxP][kMaxP][kMaxP];

int main() {
    int p, n, m; fin >> p >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Distance[i][j] = inf;
        }
        Distance[i][i] = 0;
    }
    while (m--) {
        int a, b, c; fin >> a >> b >> c;
        --a, --b;
        Distance[a][b] = c;
        Distance[b][a] = c;
    }

    for (int i = 1; i <= p; ++i) {
        fin >> destination[i];
        destination[i]--;
    }

    // virtual node in 0 :)
    destination[++p] = 0;
    for (int t = 1; t <= p; ++t) {
        int source = destination[t];
        for (int i = 0; i < n; ++i) {
            viz[i] = false;
        }
        viz[source] = true;
        while (1) {
            int mn = inf, where = -1;
            for (int i = 0; i < n; ++i) {
                if (not viz[i] and Distance[source][i] < mn) {
                    where = i;
                    mn = Distance[source][i];
                }
            }
            // expand from where
            if (where == -1) {
                break;
            }
            viz[where] = true;
            for (int i = 0; i < n; ++i) {
                if (Distance[source][i] > Distance[source][where] + Distance[where][i]) {
                    Distance[source][i] = Distance[source][where] + Distance[where][i];
                }
            }
        }
    }

    for (int c1 = 1; c1 <= p; ++c1) {
        for (int c2 = c1; c2 <= p; ++c2) {
            for (int c = 1; c <= p; ++c) {
                best[c1][c2][c] = inf;
            }
        }
        best[c1][c1][c1] = 0;
    }

    for (int l = 0; l <= p; ++l) {
        for (int c1 = 1; c1 + l <= p; ++c1) {
            int c2 = c1 + l;
            // try to merge for every node
            for (int i = 1; i <= p; ++i) {
                if (c1 <= i and i <= c2) {
                    // try to stop i in his city
                    int cost = best[c1][i - 1][i] + best[i + 1][c2][i];
                    best[c1][c2][i] = min(best[c1][c2][i], cost);
                }
            }
            
            for (int i = 1; i <= p; ++i) {
                viz[i] = false;
            }

            for (int i = 1; i <= p; ++i) {
                int mn = inf;
                int where = -1;
                for (int j = 1; j <= p; ++j) {
                    if (best[c1][c2][j] < mn) {
                        mn = best[c1][c2][j];
                        where = j;
                    }
                }

                for (int j = 1; j <= p; ++j) {
                    best[c1][c2][j] = min(best[c1][c2][j], best[c1][c2][where] + Distance[destination[where]][destination[j]]);
                }
            }
        }
    }

/*    for (int nod = 1; nod <= p; ++nod) {
        cerr << "#####\t" << destination[nod] << '\n';
        for (int c1 = 1; c1 <= p; ++c1) {
            for (int c2 = c1; c2 <= p; ++c2) {
                cerr << c1 << '\t' << c2 << '\t' << best[c1][c2][nod] << '\n';
            }
        }
    }*/

    fout << best[1][p][p];
    return 0;
}
