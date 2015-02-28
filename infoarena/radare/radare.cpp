#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("radare.in");
ofstream out("radare.out");

const int kMaxN = 3505, Mod = 31333;

int Beg[kMaxN][kMaxN], g[kMaxN];

int p2[kMaxN];
bool viz[kMaxN];
int under[kMaxN], cost[kMaxN];
vector<int> vertex[kMaxN];

void get_under(int nod) {
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i];
		if (not viz[oth]) {
			get_under(oth);
			under[nod] += under[oth] + 1;
		}
	}
}

void df(int nod) {
	viz[nod] = true;
	for (int i = 0; i < kMaxN; ++i)
		Beg[nod][i] = (g[i] * p2[under[nod]]) % Mod;
	for (int i = kMaxN - 1; i >= 0; --i)
		if (i >= cost[nod])
			g[i] = g[i - cost[nod]];
		else
			g[i] = 0;
	for (int i = 0; i < int(vertex[nod].size()); ++i) {
		int oth = vertex[nod][i];
		if (not viz[oth])
			df(oth);
	}

	for (int i = 0; i < kMaxN; ++i) {
		g[i] += Beg[nod][i];
		if (g[i] >= Mod)
			g[i] -= Mod;
	}
}

int main() {
	int n, p;
	in >> n >> p;
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}

	for (int i = 1; i <= n; ++i)
		in >> cost[i];
	p2[0] = 1;
	for (int i = 1; i <= n; ++i) {
		p2[i] = 2 * p2[i - 1];
		if (p2[i] >= Mod)
			p2[i] -= Mod;
	}

	get_under(1);
	for (int i = 1; i <= n; ++i)
		viz[i] = false;

	g[0] = 1;
	df(1);
	out << g[p] << '\n';
	in.close();
	out.close();
	return 0;
}
