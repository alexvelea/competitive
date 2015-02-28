#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define FORIT(it, v) for(vector<int> :: iterator it = (v).begin(); it != (v).end(); ++it)

ifstream in("sistem3.in");
ofstream out("sistem3.out");

const int kMaxN = 100005;

int n, Mod;

void mod(int &a) {
	while (a < 0)
		a += Mod;
	while (a >= Mod)
		a -= Mod;
}

int pow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % Mod;
		a = (1LL * a * a) % Mod;
		p >>= 1;
	}
	return rez;
}


struct Edge {
	int a, b, c;
	int sol;
	Edge() { sol = 0; }
	Edge(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
		sol = 0;
	}
	void set_sol(int _sol, int nod) {
		if (nod == a)
			sol = _sol;
		else {
			sol = - _sol;
			mod(sol);
		}
			
	}
	int oth(int nod) {
		return a + b - nod;
	}
	int get_sol(int nod, int cost) {
		if (nod == a) {
			int rez = cost - sol;
			mod(rez);
//			cerr << cost << "-" << rez << '=' << sol << '\n';
			return rez;
		} else {
			int rez = cost + sol;
			mod(rez);
//			cerr << rez << '-' << cost << '=' << sol << '\n';
			return rez;
		}
	}
} edge[kMaxN];
vector<int> vertex[kMaxN];

bool viz_m[kMaxN], viz[kMaxN];
int inv[kMaxN];
int cost[kMaxN], rez[kMaxN], nr[kMaxN];


void solve(int nod) {
	int ind = 0;

	FORIT(it, vertex[nod]) {
		if(viz_m[*it] == 0 and edge[*it].sol != -1)
			ind = *it;
	}
//	cerr << nod << '\t' << nr[nod] << '\n';
	if (ind == 0)
		assert(0);
	viz_m[ind] = true;
	// muchia ind e orientata de la nod -> oth
	// are costul egal cu cost[nod]
	int val = (1LL * inv[edge[ind].c] * cost[nod]) % Mod;
//	cerr << edge[ind].c << '#' << inv[edge[ind].c] << '\n';
//	cerr << val << '\n';
	int oth = edge[ind].oth(nod);
	edge[ind].set_sol(val, nod);

	cost[oth] -= (1LL * (Mod - val) * edge[ind].c) % Mod;
	mod(cost[oth]);

	cost[nod] = 0;
	mod(cost[oth]);
	nr[oth]--;
	nr[nod]--;
	if (nr[oth] == 1)
		solve(oth);
}

void get_rez(int nod) {
	FORIT(it, vertex[nod]) {
		int oth = edge[*it].oth(nod);
		if (viz[oth])
			continue;
		viz[oth] = true;
		if (edge[*it].sol == -1) {
			continue;
		} else {
//			cerr << nod << '\t' << oth << '\n';
			rez[oth] = edge[*it].get_sol(nod, rez[nod]);
		}
		get_rez(oth);
	}
	return ;
}

int main() {
	in >> n >> Mod;
	for (int i = 1; i <= n; ++i) {
		int a, b, c;
		in >> a >> b >> c;
		edge[i] = Edge(a, b, c);
		vertex[a].push_back(i);
		vertex[b].push_back(i);
		nr[a]++;
		nr[b]++;
	}

	for (int i = 1; i <= n; ++i)
		in >> cost[i];

	for (int i = Mod - 1; i; --i) 
 		inv[i] = pow(i, Mod - 2);
	inv[0] = inv[1] = 1;

	for (int i = 1; i <= n; ++i) {
 		if (nr[i] == 1)
			solve(i);
	}
/*	for (int i = 1; i <= n; ++i)
		cerr << cost[i] << '\t';
		cerr << '\n';

 	for (int i = 1; i <= n; ++i)
		cerr << i << '\t' << edge[i].a << '\t' << edge[i].b << '\t' << edge[i].sol << '\n';*/

	for (int i = 1; i <= n; ++i) {
		if (nr[i] != 0) {
			int ind = 0;
			FORIT(it, vertex[i])
				if (viz[*it] == false) {
					ind = *it;
					break;
				}
//			cerr << "#" << ind << "\t" << edge[ind].a << '\t' << edge[ind].b << '\n';
			nr[edge[ind].a]--;
			nr[edge[ind].b]--;

 			viz_m[ind] = true;
            edge[ind].sol = -1;

			if (nr[edge[ind].a] == 1)
				solve(edge[ind].a);
        	viz[edge[ind].a] = true;
			rez[edge[ind].a] = 0;
			get_rez(edge[ind].a);
		}
	}

	for (int i = 1; i <= n; ++i)
		out << rez[i] << '\n';
	return 0;
}
