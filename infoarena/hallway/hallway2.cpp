#include <cmath>
#include <cstdio>
 
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
 
const int max_n = 1005;
const double INF = 0x3f3f3f3f;
ifstream in("hallway.in");
 
int n, m, k;
 
pair<int,int> coord[max_n];
 
int dist[max_n][max_n], best[max_n];
bool viz[max_n];
 
int main() {
    in >> n >> m >> k;
    for (int i = 1; i <= k; ++i) {
        int x, y;
        in >> x >> y;
        coord[i] = make_pair(x, y);
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j)
            if (i != j) {
                dist[i][j] =
                    (coord[i].first-coord[j].first)
                    * (coord[i].first - coord[j].first)
                    + (coord[i].second - coord[j].second)
                    * (coord[i].second - coord[j].second);
            }
        dist[i][k + 1] = dist[k + 1][i] = coord[i].second * coord[i].second;
        dist[i][k + 2] = dist[k + 2][i] = (m - coord[i].second) * (m - coord[i].second);
    }
    dist[k + 1][k + 2] = dist[k + 2][k + 1] = m * m;
    for (int i = 1; i <= k + 2; ++i)
        best[i] = INF;
    best[k + 2] = 0;
	int rez = 0;
    while (1) {
        if (viz[k + 1]) {
            freopen("hallway.out", "w", stdout);
            printf("%.8lf", sqrt(1.0 * rez) / 2.0);
            return 0;
        }
        int ind = 0;
        double mn = INF;
        for (int i = 1; i <= k+2; ++i)
            if (!viz[i] && best[i] < mn) {
                mn = best[i];
                ind = i;
            }
        viz[ind] = true;
 		rez = max(rez, best[ind]);
        for (int i = 1; i <= k + 2; ++i)
//	        if (best[i] > dist[ind][i])
//				best[i] = dist[ind][i];
			if (viz[i])
				best[i] = min(best[i], max(dist[i][ind], best[ind]));
    }
    return 0;
}
