#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

const int max_n = 155000;

ifstream in("drumuri5.in");
ofstream out("drumuri5.out");

vector<int> vertex[2][max_n];
vector<int> brut_vertex[2][max_n];

bool viz[max_n];

vector<int> ctc_el[max_n];
stack<int> ctc_stack;
int nr_ctc;
int ctc[max_n];

queue<int> topo;
int sum[max_n];

int n, m;

void stack_df (int nod) {
	if (viz[nod]) return;
	viz[nod] = true;
	for (vector<int> :: iterator it = brut_vertex[0][nod].begin(); it != brut_vertex[0][nod].end(); ++it)
		if (!viz[*it])
			stack_df(*it);
	ctc_stack.push(nod);
}

void ctc_df (int nod) {
	if (viz[nod]) return;
	viz[nod] = true;
	ctc[nod] = nr_ctc;
	ctc_el[nr_ctc].push_back (nod);
	for (vector<int> :: iterator it = brut_vertex[1][nod].begin(); it != brut_vertex[1][nod].end(); ++it)
		if (!viz[*it])
			ctc_df (*it);
}

void make_topo (int ind) {
	stack <int> st;
 	int outgoing[max_n];
	for (int i = 0; i < max_n; ++i)
		outgoing[i] = 0;
	for (int i = 1; i <= nr_ctc; ++i)
		if (vertex[ind][i].size() == 0)
			st.push(i);
	while (!st.empty()) {
		int nod = st.top();
		st.pop();
 		topo.push(nod);
		for (vector<int> :: iterator it = vertex[ind^1][nod].begin(); it != vertex[ind^1][nod].end(); ++it) {
			++outgoing[*it];
			if (outgoing[*it] == int(vertex[ind][*it].size()))
				st.push(*it);
		}
	}
	return ;
}

void make_sums(int ind) {
	int under[max_n];
	bool viz[max_n];
	for (int i = 0; i < max_n; ++i) {
		under[i] = 0;
		viz[i] = false;
	}
	while (!topo.empty()) {
		int nod = topo.front();
		topo.pop();
 		for (vector<int> :: iterator it = vertex[ind][nod].begin(); it != vertex[ind][nod].end(); ++it) 
			if (!viz[*it]) {
				under[nod] += under[*it] + 1;
				viz[*it] = true;
			}
		sum[nod] += under[nod];
	}
}

int main() {
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
 		brut_vertex[0][a].push_back (b);
		brut_vertex[1][b].push_back(a);
	}
 	for (int i = 1; i <= n; ++i) 
		if (!viz[i])
			stack_df(i);
	for (int i = 1; i <= n; ++i) 
		viz[i] = false;
	while (!ctc_stack.empty()) {
		if (!viz[ctc_stack.top()]) {
			++nr_ctc;
			ctc_df(ctc_stack.top());
		}
		ctc_stack.pop();
	}

 	for (int i = 1; i <= n; ++i) 
		for (vector<int> :: iterator it = brut_vertex[0][i].begin(); it != brut_vertex[0][i].end(); ++it)
			if (ctc[i] != ctc[*it])
				vertex[0][ctc[i]].push_back(ctc[*it]);

	for (int i = 1; i <= nr_ctc; ++i) {
		sort (vertex[0][i].begin(), vertex[0][i].end());
 		vertex[0][i].resize (unique (vertex[0][i].begin(), vertex[0][i].end()) - vertex[0][i].begin());
		for (vector<int> :: iterator it = vertex[0][i].begin(); it != vertex[0][i].end(); ++it)
			vertex[1][*it].push_back(i);
	}
//	for (int i = 1; i <= nr_ctc; ++i) {
//		for (vector<int> :: iterator it = ctc_el[i].begin(); it != ctc_el[i].end(); ++it) 
//			cerr << *it << " # ";
//		cerr << "\n";
//	}
	for (int t = 0; t < 2; ++t) {
		make_topo (t);
		make_sums (t);
	}
	vector<int> rez;
 	for (int i = 0; i <= nr_ctc; ++i) 
		if (sum[i] == nr_ctc - 1)
			for (vector<int> :: iterator it = ctc_el[i].begin(); it != ctc_el[i].end(); ++it)
				rez.push_back (*it);
	sort (rez.begin(), rez.end());
	out << rez.size() << "\n";
	for (vector<int> :: iterator it = rez.begin(); it != rez.end(); ++it)
		out << *it << " ";
	return 0;
}

