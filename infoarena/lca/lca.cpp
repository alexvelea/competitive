#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("lca.in");
ofstream out("lca.out");

const int kMaxN = 100005;

vector<int> vertex[kMaxN];
bool viz[kMaxN];
int first[kMaxN], RMQ[20][2 * kMaxN], deep[kMaxN], nr_rmq;

void df(int nod) {
 	RMQ[0][++nr_rmq] = nod;   
	first[nod] = nr_rmq;
	for (int i = 0; i < vertex[nod].size(); ++i) {
		int oth = vertex[nod][i];
 		deep[oth] = deep[nod] + 1;   	
		df(oth);
		RMQ[0][++nr_rmq] = nod;
	}
}


int lca(int a, int b) {
	a = first[a];
	b = first[b];
	if (a > b)
		swap(a, b);
	if (a == b)
		return a;
	int d = 0;
	while ((1 << d) < (b - a + 1))
		++d;
	--d;
	if (deep[RMQ[d][a]] < deep[RMQ[d][b - (1 << d) + 1]])
		return RMQ[d][a];
	return RMQ[d][b - (1 << d) + 1];
}


void make_RMQ() {
	for (int l = 1; (1 << l) <= nr_rmq; ++l)
		for (int st = 1; st + (1 << l) <= nr_rmq; ++st) {
			int dr = st + (1 << (l - 1));
			if (deep[RMQ[l - 1][st]] < deep[RMQ[l - 1][dr]])
				RMQ[l][st] = RMQ[l - 1][st];
			else
				RMQ[l][st] = RMQ[l - 1][dr];
		}
		
}


int main() {
 	int n, m;
	in >> n >> m;
	for (int i = 2; i <= n; ++i) {
		int a;
		in >> a;
		vertex[a].push_back(i);
	}
 	df(1);
	make_RMQ();
	while (m--) {
		int a, b;
		in >> a >> b;
		out << lca(a, b) << '\n';
	}
	return 0;
}

