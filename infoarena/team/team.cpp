//Problem team @ 17-06-2015
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxP = 55, kMaxN = 505;

#define int64 long long

ifstream fin("team.in");
ofstream fout("team.out");

int best[kMaxP][kMaxP][kMaxN];
bitset<kMaxN> viz[kMaxP][kMaxP];

typedef tuple<int, int, int, int> DjkState; // cost, s1, s2, nod

vector<pair<int, int> > vertex[kMaxN];
int destination[kMaxP];

int main() {
    int p, n, m; fin >> p >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c; fin >> a >> b >> c;
        vertex[a].push_back(make_pair(b, c));
        vertex[b].push_back(make_pair(a, c));
    }

    for (int s1 = 1; s1 <= p; ++s1) {
        for (int s2 = s1; s2 <= p; ++s2) {
            for (int nod = 1; nod <= n; ++nod) {
                best[s1][s2][nod] = inf;
            }
        }
    }

    priority_queue<DjkState> pq;

    for (int i = 1; i <= p; ++i) {
        fin >> destination[i];
        best[i][i][destination[i]] = 0;
        pq.push(make_tuple(0, i, i, destination[i]));
    }

    while (pq.size() and viz[1][p][1] == false) {
        int cost, s1, s2, nod;
        tie(cost, s1, s2, nod) = pq.top();
        pq.pop();
        if (viz[s1][s2][nod]) {
            continue;
        }
        viz[s1][s2][nod] = true;

        //go on edges
        for (auto itr : vertex[nod]) {
            int cost = best[s1][s2][nod] + itr.second;
            int oth = itr.first;
            if (best[s1][s2][oth] > cost) {
                best[s1][s2][oth] = cost;
                pq.push(make_tuple(-cost, s1, s2, oth));
            }
        }

        //unite things on left
        for (int c1 = 1; c1 < s1; ++c1) {
            int cost = best[c1][s1 - 1][nod] + best[s1][s2][nod];
            if (best[c1][s2][nod] > cost) {
                best[c1][s2][nod] = cost;
                pq.push(make_tuple(-cost, c1, s2, nod));
            }
        }

        //unite things on right
        for (int c2 = s2 + 1; c2 <= p; ++c2) {
            int cost = best[s2 + 1][c2][nod] + best[s1][s2][nod];
            if (best[s1][c2][nod] > cost) {
                best[s1][c2][nod] = cost;
                pq.push(make_tuple(-cost, s1, c2, nod));
            }
        }
    }

    /*for (int i = 1; i <= n; ++i) {
        cerr << "########\n";
        for (int s1 = 1; s1 <= p; ++s1) {
            for (int s2 = s1; s2 <= p; ++s2) {
                cerr << s1 << '\t' << s2 << '\t' << best[s1][s2][i] << '\n';
            }
        }
    }*/
    fout << best[1][p][1] << '\n';
	return 0;
}
