#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

ifstream in("base3.in");
ofstream out("base3.out");
const int max_n = 16005, inf = 0x3f3f3f3f;

string txt[3];
priority_queue<pair<int,int> > pq;
int best[max_n], viz[max_n], s[max_n];

int main() {
	for (int i = 0; i < 3; ++i) {
		in >> txt[i];
		s[i] = txt[i].size();
	}
	for (int i = 1; i < max_n; ++i)
		best[i] = inf;
	pq.push(make_pair(0,0));
	while (pq.size()) {
		int nod = pq.top().second;
		pq.pop();
		if (viz[nod])
			continue;
		viz[nod] = true;
		for (int i = 0; i < 3; ++i) {
			int n_cost = best[nod] + s[i];
			int n_nod = abs(nod - s[i]);
			if (best[n_nod] > n_cost) {
				best[n_nod] = n_cost;
				pq.push(make_pair(- n_cost, n_nod));
			}
		}
	}
	int mx = inf;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < s[i]; ++j)
			if (txt[i][j] == '1') {
				int nr = abs((s[i] - 1 - 2 * j));
				if (mx > best[nr] + s[i])
					mx = best[nr] + s[i];
			}
	if (mx == inf)
		out << '0';
	else
		out << mx << '\n';
	return 0;

}
