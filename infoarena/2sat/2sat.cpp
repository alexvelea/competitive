#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("2sat.in");
ofstream out("2sat.out");

const int kMaxN = 100005;

vector<int> vertex[2 * kMaxN];
#define vertex (vertex + kMaxN)

bool viz[2 * kMaxN];
#define viz (viz + kMaxN)

bool rez[2 * kMaxN];
#define rez (rez + kMaxN)

int topo[2 * kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (int itr : vertex[nod]) 
		if (not viz[itr])
			df(itr);
	topo[++topo[0]] = nod;
}

int main() {
	int n, m;
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(-b);
		vertex[b].push_back(-a);
	}

	for (int i = 1; i <= n; ++i)
		if (not viz[i])
			df(i);
	
	for (int i = 1; i <= 2 * n; ++i) 
		if (not rez[topo[i]] and not rez[-topo[i]]) {
			rez[topo[i]] = false;
			rez[-topo[i]] = true;
		}
	
    bool imp = true;

	for (int i = 1; i <= n; ++i) {
		for (int itr : vertex[i])
			if (not rez[i] and not rez[-itr])
				imp = false;
	}

	if (not imp) 
		out << "-1\n";
	else {
		for (int i = 1; i <= n; ++i)
			out << rez[i] << ' ';
	}
    return 0;
}
