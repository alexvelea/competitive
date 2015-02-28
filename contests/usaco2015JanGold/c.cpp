//Problem C from Codeforces Round usaco2015JanGold
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("grass.in");
ofstream out("grass.out");

int df[kMaxN], topo[kMaxN];
int _up[kMaxN], _down[kMaxN];
bool viz[kMaxN];

vector<int> ctcEl[kMaxN];
vector<int> vertex[kMaxN], vertexBack[kMaxN];
vector<int> ctcVertex[kMaxN], ctcVertexBack[kMaxN];

int nrCtc, ctc[kMaxN];

void dfForward(int nod) {
	viz[nod] = true;
	for (auto itr : vertex[nod]) {
		if (viz[itr])
			;
		else
			dfForward(itr);
	}
	df[++df[0]] = nod;
}

void dfBack(int nod, int &nrCtc) {
	viz[nod] = true;
	ctc[nod] = nrCtc;
	ctcEl[nrCtc].push_back(nod);
	for (auto itr : vertexBack[nod]) {
		if (viz[itr] == false) {
			dfBack(itr, nrCtc);
		}
	}
}

void topoCtc(int nod) {
	viz[nod] = true;
	for (auto itr : ctcVertex[nod]) {
		if (viz[itr] == false) {
			topoCtc(itr);
		}
	}
	topo[++topo[0]] = nod;
}

void topoCtcBack(int nod) {
	viz[nod] = true;
	for (auto itr : ctcVertexBack[nod]) {
		if (viz[itr] == false) {
			topoCtc(itr);
		}
	}
	topo[++topo[0]] = nod;
}

int main() {
	int n, m;
    in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertexBack[b].push_back(a);
	}

	for (int i = 1; i <= n; ++i) {
		if (not viz[i]) {
			dfForward(i);
		}
	}

	for (int i = 1; i <= n; ++i) {
		viz[i] = false;
	}

	for (int i = n; i; --i) {
		int nod = df[i];
		if (not viz[nod]) {
			++nrCtc;
			dfBack(nod, nrCtc);
		}
	}

//	for (int i = 1; i <= n; ++i) {
//		cerr << i << '\t' << ctc[i] << '\n';
//	}

	for (int i = 1; i <= n; ++i) {
		for (auto itr : vertex[i]) {
			if (ctc[i] != ctc[itr]) {
				ctcVertex[ctc[i]].push_back(ctc[itr]);
				ctcVertexBack[ctc[itr]].push_back(ctc[i]);
			}
		}
	}

	for (int i = 1; i <= nrCtc; ++i) {
		viz[i] = false;
	}

	for (int i = 1; i <= nrCtc; ++i) {
		if (viz[i] == false) {
			topoCtc(i);
		}
	}

    _down[ctc[1]] = ctcEl[ctc[1]].size();

	for (int i = nrCtc; i; --i) {
		int nod = topo[i];
		if (_down[nod] != 0) {
			for (auto itr : ctcVertex[nod]) {
				_down[itr] = max(_down[itr], _down[nod] + int(ctcEl[itr].size()));
			}
		}
	}

	for (int i = 1; i <= nrCtc; ++i) {
		viz[i] = false;
	}

 	topo[0] = 0;
	for (int i = 1; i <= nrCtc; ++i) {
		if (viz[i] == false) {
			topoCtcBack(i);
		}
	}

	_up[ctc[1]] = ctcEl[ctc[1]].size();

 	for (int i = nrCtc; i; --i) {
		int nod = topo[i];
		if (_up[nod] != 0) {
			for (auto itr : ctcVertexBack[nod]) {
				_up[itr] = max(_up[itr], _up[nod] + int(ctcEl[itr].size()));
			}
		}
	}   

	int mx = 0;
	ctcVertex[ctc[1]].push_back(ctc[1]);
	for (int i = 1; i <= nrCtc; ++i) {
		for (auto itr : ctcVertex[i]) {
			if (_up[i] != 0 and _down[itr] != 0) {
				if (mx < _up[i] + _down[itr]) {
					mx = _up[i] + _down[itr];
				}
			}
		}
	}

	mx -= int(ctcEl[ctc[1]].size());
	out << mx << '\n';
	return 0;
}
