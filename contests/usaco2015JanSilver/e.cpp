//Problem A from Codeforces Round usaco2015JanBronz
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005;

ifstream in("cowroute.in");
ofstream out("cowroute.out");

int64 best[kMaxN], cost[kMaxN], oldBest[kMaxN];
int minTime[kMaxN];
vector<int> vertex[kMaxN];

int main() {
    int a, b, q;
    in >> a >> b >> q;
    for (int i = 1; i <= q; ++i) {
        int n;
        in >> cost[i] >> n;
        while (n--) {
            int x;
            in >> x;
            vertex[i].push_back(x);
        }
    }
    
    for (int i = 1; i < kMaxN; ++i) {
        best[i] = 1LL * inf * inf;
        minTime[i] = inf;
    }
    minTime[a] = 0;
    best[a] = 0;
    
    for (int t = 1; t < kMaxN; ++t) {
        for (int i = 0; i < kMaxN; ++i) {
            oldBest[i] = best[i];
        }
        for (int i = 1; i <= q; ++i) {
            int64 mn = 1LL * inf * inf;
            int dist = 0, poz = -inf;
            for (int itr : vertex[i]) {
                ++dist;
                if (mn > oldBest[itr] + cost[i]) {
                    mn = oldBest[itr] + cost[i];
                    poz = dist - minTime[itr];
                }
                if (mn == oldBest[itr] and dist + minTime[itr] > poz) {
                    poz = dist - minTime[itr];
                }
                
                mn = min(mn, oldBest[itr] + cost[i]);
                if (best[itr] > mn) {
                    best[itr] = mn;
                    minTime[itr] = dist - poz;
                }
				if (mn == best[itr] and minTime[itr] > dist - poz) {
					minTime[itr] = dist - poz;
				}
            }
        }
    }
    if (best[b] == 1LL * inf * inf) {
        best[b] = -1;
        minTime[b] = -1;
    }
    
	out << best[b] << ' ' << minTime[b] << '\n';
    out.close();
    return 0;
}
