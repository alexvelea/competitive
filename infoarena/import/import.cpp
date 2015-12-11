//Problem import from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include <cassert>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 230;

ifstream in("import.in");
ofstream out("import.out");

int n, m, k;

queue<int> Deq;
bool inside[kMaxN], viz[kMaxN];
int best[kMaxN], rez[kMaxN];

vector<pair<int, int> > gss[kMaxN];
vector<int>vertex[kMaxN];

void solve(int nod) {
	viz[nod] = true;
	for (int itr : vertex[nod]) {
		if (viz[itr] == true) {
			rez[nod] = best[nod] - best[itr];
		} else {
			solve(itr);
		}
	}
}
int main() {
	in >> n >> m >> k;
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}

	for (int i = 1; i <= m; ++i) {
		int a, b, c, x;
		in >> a >> b >> c >> x;
		if (a > b)
			swap(a, b);
		
		if (x == 0)
			;
		else {
			c--;
			c *= -1;
			swap(a, b);
		}

		gss[a].push_back(make_pair(b, -c));

	}
	for (int i = 0; i <= n; ++i)
		gss[0].push_back(make_pair(i, 0));
		
	for (int i = 0; i <= n; ++i)
		best[i] = inf;
	best[0] = 0;
	Deq.push(0);
	inside[0] = true;
 	
    for (int i = 1; i <= n; ++i)
		for (pair<int, int> itr : gss[i])
			cerr << i << '\t' << itr.first << '\t' << itr.second << '\n';

	while (!Deq.empty()) {
		int nod = Deq.front();
		Deq.pop();
		inside[nod] = false;
		for (pair<int, int> itr : gss[nod])
			if (best[itr.first] > best[nod] + itr.second) {
				best[itr.first] = best[nod] + itr.second;
				if (not inside[itr.first]) {
					Deq.push(itr.first);
					inside[itr.first] = true;
				}
			}
	}
	for (int i = k + 1; i <= n; ++i)
		best[i] *= -1;
	viz[0] = true;
	solve(1);
	for (int i = 1; i <= n; ++i)
		out << rez[i] << ' ';

	return 0;
}
