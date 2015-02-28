#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define FORIT(it, v) for(vector<pair<int, int> > :: iterator it = (v).begin(); it != (v).end(); ++it)

const int max_n = 1005;
const double eps = 0.000001;
ifstream in("ciclu.in");

int n, m;
vector<pair<int, int> > vertex[max_n];

bool find(double target) {
	double best[max_n];
	bool inside[max_n];
	int times[max_n];
	queue<int> q;
	for (int i = 0; i <= n; ++i) {
		best[i] = 1000000.0;
		inside[i] = false;
		times[i] = 0;
	}
	q.push(0);
	best[0] = 0.0;
	while(q.size()) {
		int nod = q.front();
		inside[nod] = false;
		q.pop();
		FORIT(it, vertex[nod])
			if (best[it->first] > best[nod] + it->second + eps - target) {
				times[it->first] ++;
				if (times[it->first] > n)
					return true;
				best[it->first] = best[nod] + it->second - target;
				if (not inside[it->first]) {
					inside[it->first] = true;
					q.push(it->first);
				}
			}
	}
	return false;
}

int main() {
	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b, c;
		in >> a >> b >> c;
		vertex[a].pb(mp(b, c));
	}
	for (int i = 1; i <= n; ++i)
		vertex[0].pb(mp(i,100000));
	double p = 100000.0, rez = 0.0;
	for (int t = 32; t; --t, p /= 2.0)
		if (find(p + rez))
			;
		else
			rez += p;
	freopen("ciclu.out","w",stdout);
	printf("%.2f\n", rez);
	return 0;

}
