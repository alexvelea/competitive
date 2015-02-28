#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1005, inf = 0x3f3f3f3f;

ifstream in("maxflow.in");
ofstream out("maxflow.out");

struct Edge {
	int a, b;
	int c, f;
	Edge() {
		a = b = c = f = 0;
	}
	Edge(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
		f = 0;
	}
	
	bool pump_flow(int nod) {
		if (nod == a)
			return f != c;
		return f > 0;
	}
	
	int flow_to(int nod) {
		if (nod == b)
			return c - f;
		return f;
	}

	void add_flow_to(int nod, int val) {
		if (nod == b)
			f += val;
		else
			f -= val;
	}

	int other(int nod) {
		return a + b - nod;
	}
};

vector<Edge> edge;
vector<int> edge_id[kMaxN];
int father[kMaxN];

void add_edge(int a, int b, int c) {
	edge_id[a].push_back(int(edge.size()));
	edge_id[b].push_back(int(edge.size()));
 	edge.push_back(Edge(a, b, c));   
}

int n, m, max_flow;

bool find_flow() {
	for (int i = 1; i <= n; ++i) {
		father[i] = 0;
	}
	father[1] = 1;
	int bfs[kMaxN], st = 1;
	bfs[0] = 1;
	while (st > 0) {
		int ind = rand() % st;
		int nod = bfs[ind];
		bfs[ind] = bfs[--st];
        for (int itr : edge_id[nod]) {
			int oth = edge[itr].other(nod);
			if (father[oth] == 0 and edge[itr].pump_flow(nod)) {
				father[oth] = itr;
				bfs[st++] = oth;
			}
		}
	}
	if (not father[n])
		return false;
 	int mn = inf;
	for (int nod = n; nod != 1; nod = edge[father[nod]].other(nod))
		mn = min(mn, edge[father[nod]].flow_to(nod));
 	
	for (int nod = n; nod != 1; nod = edge[father[nod]].other(nod))
		edge[father[nod]].add_flow_to(nod, mn);
	max_flow += mn;
	return true;
}


int main() {
	edge.push_back(Edge());
	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b, c;
		in >> a >> b >> c;
		add_edge(a, b, c);
	}
	while (find_flow())
		;	
	out << max_flow << '\n';
	return 0;
}

