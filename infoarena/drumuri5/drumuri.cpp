#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("drumuri5.in");
ofstream out("drumuri5.out");

const int inf = 0x3f3f3f3f, kMaxN = 150005;

vector<int> init_vertex[kMaxN], init_vertex_back[kMaxN];
int ctc_id[kMaxN], nr_ctc;
vector<int> ctc_el[kMaxN];
bool viz[kMaxN];
stack<int> ctc_st;

vector<int> vertex[kMaxN], vertex_back[kMaxN];

int topo[kMaxN];
int under[kMaxN], rez_count[kMaxN];
vector<int> rez_el;

void ctc_df(int nod) {
	viz[nod] = true;
	for (int itr = 0; itr < int(init_vertex[nod].size()); ++itr) {
		int oth = init_vertex[nod][itr];
		if (not viz[oth])
			ctc_df(oth);
	}
	ctc_st.push(nod);
}

void ctc_df_back(int nod) {
	viz[nod] = true;
	ctc_id[nod] = nr_ctc;
	ctc_el[nr_ctc].push_back(nod);
	for (int itr = 0; itr < int(init_vertex_back[nod].size()); ++itr) {
		int oth = init_vertex_back[nod][itr];
		if (not viz[oth])
			ctc_df_back(oth);
	}
}

void topo_df(int nod) {
	viz[nod] = true;
	for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
		int oth = vertex[nod][itr];
		if (not viz[oth])
			topo_df(oth);
	}
	topo[++topo[0]] = nod;
}

void solve() {
	for (int i = 1; i <= topo[0]; ++i) {
		int nod = topo[i];
		for (int itr = 0; itr < int(vertex[nod].size()); ++itr) {
			int oth = vertex[nod][itr];
			rez_count[nod] += under[oth];
			under[nod] += under[oth];
			under[oth] = 0;
		}
	}
	return ;
}

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b;
    	in >> a >> b;
		init_vertex[a].push_back(b);
		init_vertex_back[b].push_back(a);
	}
	in.close();
	for (int i = 1; i <= n; ++i)
		if (not viz[i])
		    ctc_df(i);
	for (int i = 1; i <= n; ++i)
		viz[i] = false;
	while (not ctc_st.empty()) {
		int nod = ctc_st.top();
		ctc_st.pop();
		if (not viz[nod]) {
			++nr_ctc;
 			ctc_df_back(nod);
		}
	}

//	for (int i = 1; i <= n; ++i) 
//		cerr << i << '\t' << ctc_id[i] << '\n';

	for (int nod = 1; nod <= n; ++nod) {
		for (int itr = 0; itr < int(init_vertex[nod].size()); ++itr) {
			int oth = init_vertex[nod][itr];
			if (ctc_id[nod] != ctc_id[oth]) 
				vertex[ctc_id[nod]].push_back(ctc_id[oth]);
		}
	}

	for (int nod = 1; nod <= nr_ctc; ++nod) {
		sort(vertex[nod].begin(), vertex[nod].end());
        vertex[nod].resize(unique(vertex[nod].begin(), vertex[nod].end()) - vertex[nod].begin());
		for (int j = 0; j < int(vertex[nod].size()); ++j)
			vertex_back[vertex[nod][j]].push_back(nod);
	}

	for (int i = 1; i <= nr_ctc; ++i)
		viz[i] = false;
	for (int i = 1; i <= nr_ctc; ++i)
		if (not viz[i])
			topo_df(i);

	for (int i = 1; i <= nr_ctc; ++i)
		under[i] = 1;

	solve();

    for (int i = 1; i <= nr_ctc; ++i) {
		swap(vertex[i], vertex_back[i]);
		under[i] = 1;
	}

	reverse(topo + 1, topo + nr_ctc + 1);

	solve();

	for (int i = 1; i <= nr_ctc; ++i)
		if (rez_count[i] == nr_ctc - 1)
			for (int itr = 0; itr < int(ctc_el[i].size()); ++itr)
				rez_el.push_back(ctc_el[i][itr]);

	sort(rez_el.begin(), rez_el.end());
	out << rez_el.size() << '\n';
	for (int itr = 0; itr < int(rez_el.size()); ++itr)
		out << rez_el[itr] << ' ';
 	out.close();
    return 0;
}
