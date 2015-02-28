#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 100005;

ifstream in("ctc.in");
ofstream out("ctc.out");

vector<int> vertex[kMaxN], vertexb[kMaxN], comp[kMaxN];
bool viz[kMaxN];
int nr_comp, nr_df, df_nodes[kMaxN];

void df(int nod) {
	viz[nod] = true;
	for (int itr : vertex[nod])
		if (not viz[itr])
			df(itr);
	++nr_df;
	df_nodes[nr_df] = nod;
}

void df2(int nod) {
	viz[nod] = true;
	comp[nr_comp].push_back(nod);
	for (int itr : vertexb[nod])
		if (not viz[itr])
			df2(itr);
}

int main() {
	int n, m;
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertexb[b].push_back(a);
	}
 	for (int i = 1; i <= n; ++i)
		if (not viz[i])
			df(i);
	for (int i = 1; i <= n; ++i)
		viz[i] = false;
	for (int i = n; i; --i) {
		int nod = df_nodes[i];
		if (viz[nod] == false) {
			++nr_comp;
			df2(nod);
		}
	}
	out << nr_comp << '\n';
	for (int i = 1; i <= nr_comp; ++i) {
		sort(comp[i].begin(), comp[i].end());
		for (auto itr : comp[i])
			out << itr << ' ';
		out << '\n';
	}
	return 0;
}
