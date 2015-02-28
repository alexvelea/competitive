//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

ifstream in("autobuze2.in");
ofstream out("autobuze2.out");

const int inf = 0x3f3f3f3f, kMaxN = 100005, kMaxB = 105;

vector<int> route[kMaxB];
vector<int> route_from[kMaxN];

int best[kMaxN];
bool viz[kMaxN];

priority_queue<pair<int, int> > pq;

int main() {
	int n, m;
	in >> n >> m;
    while (m--) {
		int a, b;
		in >> a >> b;
	}
	int b;
	in >> b;
	while (b--) {
		int ind;
		in >> ind;
 		while (ind--) {
			int el;
			in >> el;
			route[b].push_back(el);
			route_from[el].push_back(b);
		}
	}

	for (int i = 1; i <= n; ++i) 
		best[i] = inf;
	best[1] = 0;
	pq.push(make_pair(0, 1));
	while (not pq.empty()) {
    	int nod = pq.top().second;
		pq.pop();
		if (viz[nod])
			continue;
    	viz[nod] = true;
		for (int itr : route_from[nod]) {
			int i = 0;
			while (route[itr][i] != nod) {
				++i;
			}
			int c = best[nod];
// 			if (i == (c % route[itr].size()) and nod != 1)
//				c += route[itr].size();   		
			c += (i - (c % route[itr].size()) + route[itr].size()) % route[itr].size();
//			cerr << nod << '\t' << itr << '\t' << c << '\n';
			++c;
			i++;
			if (i == route[itr].size())
				i = 0;
 			while (route[itr][i] != nod) {
				int a = route[itr][i];
				if (best[a] > c) {
// 			    	cerr << best[nod] << '\t' << a << '\t' << c << '\n';   				
					best[a] = c;
					pq.push(make_pair(-best[a], a));
				}
				i++;
				if (i == route[itr].size())
					i = 0;
				c++;
			}
		}
	}
	if (best[n] == inf) 
		out << "Iesim la un suc?";
	else
		out << best[n] << '\n';
	return 0;
}
