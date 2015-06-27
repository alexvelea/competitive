//Problem ecotraseu from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream fin("ecotraseu.in");
ofstream fout("ecotraseu.out");

int a, b;

bool viz[kMaxN];
vector<pair<int, int> > vertex[kMaxN];

struct Subgraph {
	int lazy;
	set<pair<int, int> > s;
	Subgraph() {
		lazy = 0;
		s.insert(make_pair(0, 0));
	}
	Subgraph(int _nod) {
		lazy = 0;
		s.insert(make_pair(0, _nod));
	}
	~Subgraph() {
		s.clear();
	}
};

Subgraph df(int nod) {
	viz[nod] = true;
	if (vertex[nod].size() == 1) {
		return Subgraph(nod);
	}

 	vector<Subgraph> under;
	under.reserve(vertex[nod].size() - 1);
	for (auto itr : vertex[nod]) {
		if (viz[itr.first])
			continue;
		under.push_back(df(itr.first));
		under.back().lazy += itr.second;
	}
 	int where = 0;
	for (int i = 1; i < int(under.size()); ++i) {
		if (under[i].s.size() > under[where].s.size()) {
			where = i;
		}
	}

/*	cerr << nod << "---->\n";
	for (auto itr : under) {
		cerr << "---->\t";
		for (auto itr2 : itr.s) {
			cerr << itr2.first + itr.lazy << ' ' << itr2.second << '\t';
		}
		cerr << '\n';
	}*/

	for (int i = 0; i < int(under.size()); ++i) {
		if (i != where) {
			// cautam prima data
 			for (auto itr : under[i].s) {
				int v = - (itr.first + under[i].lazy) - under[where].lazy;
				auto fnd = lower_bound(under[where].s.begin(), under[where].s.end(), make_pair(v, 0));
				if (fnd != under[where].s.end() and fnd->first == v) {
					a = itr.second;
					b = fnd->second;
				}
			}
			for (auto itr2 : under[i].s) {
				pair<int, int> itr = itr2;
				itr.first += under[i].lazy - under[where].lazy;
				under[where].s.insert(itr);
			}
		}
	}
	return under[where];
}

int main() {
	int t; fin >> t;
	while (t--) {
		int n; fin >> n;
		for (int i = 1; i <= n; ++i) {
			vertex[i].clear();
			viz[i] = false;
		}
		for (int i = 1; i < n; ++i) {
			int a, b, c; fin >> a >> b >> c;
			vertex[a].push_back(make_pair(b, c));
			vertex[b].push_back(make_pair(a, c));
		}
 		int nod = 0;
		for (int  i = 1; i <= n; ++i) {
			if (vertex[i].size() > 1) {
				nod = i;
			}
		}
		if (nod == 0) {
			fout << "1 2\n";
		} else {
			df(nod);
			fout << a << ' ' << b << '\n';
		}
	}
	return 0;
}
