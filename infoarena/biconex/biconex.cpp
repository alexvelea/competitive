#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("biconex.in");
ofstream out("biconex.out");

const int kMaxN = 100005;

vector<vector<int> > rez;
vector<int> vertex[kMaxN];

int deep[kMaxN], low[kMaxN];
stack<int> biconex_st;

void new_cb(int nod) {
	vector<int> r;
	while (1) {
		r.push_back(biconex_st.top());
		if (biconex_st.top() == nod)
			break;
		biconex_st.pop();
	}
	biconex_st.pop();

	rez.push_back(r);
}

void biconex(int nod, int parent, int d) {
	deep[nod] = low[nod] = d;
	biconex_st.push(nod);
	for (auto itr : vertex[nod]) {
		if (itr == parent)
			continue;
 		if (not deep[itr]) {
			biconex(itr, nod, d + 1);
			if (low[itr] >= deep[nod]) {
				new_cb(itr);
				rez.back().push_back(nod);
			}
			low[nod] = min(low[nod], low[itr]);
		} else {
			low[nod] = min(low[nod], deep[itr]);
		}
	}
}

int main() {
	int n, m;
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
	}

	biconex(1, 0, 1);
	out << rez.size() << '\n';
	for (int i = 0; i < rez.size(); ++i) {
		sort(rez[i].begin(), rez[i].end());
		for (auto itr : rez[i])
			out << itr << ' ';
		out << '\n';
	}
    return 0;
}
