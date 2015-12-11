//Problem banuti from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int kMaxN = 50005, kMaxV = 5005;
const int64 inf = 1LL * 0x3f3f3f3f * 0x3f3f3f3f;

ifstream in("banuti.in");
ofstream out("banuti.out");

int64 el[kMaxN], best[kMaxV], rez[kMaxV];
bool viz[kMaxV];

priority_queue<pair<int64, int> > pq;
vector<pair<int, int> > edge;

int main() {
	int n;
	in >> n;
	int64 mnv = inf;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
		if (mnv > el[i])
			mnv = el[i];
	}
	
	for (int i = 0; i < mnv; ++i)
		best[i] = inf;
	best[0] = 0;

	for (int i = 1; i <= n; ++i)
		if (best[el[i] % mnv] > el[i])
			best[el[i] % mnv] = el[i];
	
    for (int i = 0; i < mnv; ++i) {
		if (best[i] != inf) {
 			pq.push(make_pair(-best[i], i));
			edge.push_back(make_pair(i, best[i]));
		}
	}

	while (pq.size()) {

		int nod = pq.top().second; pq.pop();
		if (viz[nod])
			continue;
		viz[nod] = true;
    	for (pair<int, int> itr : edge) {
			if (not viz[(itr.first + nod) % mnv] and best[(itr.first + nod) % mnv] > best[nod] + itr.second) {
				best[(itr.first + nod) % mnv] = best[nod] + itr.second;
				pq.push(make_pair(-best[(itr.first + nod) % mnv], (itr.first + nod) % mnv));
			}
		}
	}
	int64 mx = 0;
	for (int i = 0; i < mnv; ++i)
		if (mx < best[i])
			mx = best[i];
	if (mx == inf)
		out << "-1\n";
	else
		out << mx - mnv << '\n';
	return 0;
}
