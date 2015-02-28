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
int minTime[kMaxN], oldMinTime[kMaxN];
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
			oldMinTime[i] = minTime[i];
		}
        for (int i = 1; i <= q; ++i) {
            int64 mn = 1LL * inf * inf;
			int dist = inf;
            for (int itr : vertex[i]) {
				dist++;
				if (mn > oldBest[itr] + cost[i]) {
					mn = oldBest[itr] + cost[i];
					dist = oldMinTime[itr];
				}
				
				if (mn == oldBest[itr] + cost[i] and dist > oldMinTime[itr]) {
					dist = oldMinTime[itr];
				}

            	if (best[itr] > mn) {
					best[itr] = mn;
					minTime[itr] = dist;
				}
				if (best[itr] == mn and minTime[itr] > dist) {
					minTime[itr] = dist;
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
