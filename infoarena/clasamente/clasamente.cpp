#include <cassert>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int max_n = 135, INF = 0x3f3f3f3f;
vector<int> vertex[max_n];

int from[max_n], best[max_n];
int inq[max_n];

int max_flow, flow_cost;

int source, sink;

struct edge {
	int a, b, c, cost, f;
	edge() {
		a = b = c = cost = f;
	}
	edge (int _a, int _b, int _c, int _cost) {
		a = _a;
		b = _b;
		c = _c;
		cost = _cost;
		f = 0;
	}
	int other (int nod) {
		return a + b - nod;
	}
	int get_flow (int nod) {
		if (nod == a)
			return c-f;
		return f;
	}
	int get_flow_back (int nod) {
		return get_flow(other(nod));
	}
	void set_flow(int nod, int _f) {
		if(nod == a) {
			assert (f+_f <= c);
			f += _f;
		} else {
			assert (f >= _f);
			f -= _f;
		}
	}
	void set_flow_back (int nod, int _f) {
		set_flow (other(nod), _f);
	}
	int get_cost (int nod) {
		if (nod == a)
			return cost;
		return -cost;
	}
};

vector<edge> edges;

void add_edge (int a, int b, int c, int cost) {
 	vertex[a].push_back (edges.size());
	vertex[b].push_back (edges.size());
	edges.push_back (edge (a, b, c, cost));
}

void clear_flow() {
	for (int i = 0; i < max_n; ++i) {
		from[i] = 0;
        best[i] = INF;
		inq[i] = false;
	}
}

bool get_flow() {
	clear_flow();
	queue<int> que;
	que.push(source);
	inq[source] = true;
	best[source] = 0;
	bool good = false;
	while (!que.empty()) {
       	int nod = que.front();
		que.pop();
		inq[nod] = false;
		if (nod == sink)
			good = true;
        for (vector<int> :: iterator it_edge = vertex[nod].begin(); it_edge != vertex[nod].end(); ++it_edge) {
			if (edges[*it_edge].get_flow(nod)) {
				if (best[edges[*it_edge].other(nod)] > best[nod] + edges[*it_edge].get_cost(nod)) {
					from[edges[*it_edge].other(nod)] = *it_edge;
			   		best[edges[*it_edge].other(nod)] = best[nod] + edges[*it_edge].get_cost(nod);
					if (!inq[edges[*it_edge].other(nod)]) {
						que.push(edges[*it_edge].other(nod));
						inq[edges[*it_edge].other(nod)] = true;
				 	}   	
				} 
			}
		}
	}
	if (!good)
		return false;
	int mn = INF;
	for (int nod = sink; nod != source; nod = edges[from[nod]].other(nod))
		mn = min (mn, edges[from[nod]].get_flow_back(nod));
	for (int nod = sink; nod != source; nod = edges[from[nod]].other(nod))
		edges[from[nod]].set_flow_back (nod, mn);
	flow_cost += best[sink] * mn;
	max_flow += mn;
	return true;
}

void clear_edges() {
	for (int i = 0; i < max_n; ++i) {
		vertex[i].clear();
	}
}

ifstream fin("clasamente.in");
ofstream fout("clasamente.out");

unordered_map<pair<char, int>, int> nr;

void makeEdges(int nrE) {
 	source = max_n - 2;
	sink = max_n - 1;

	int start = 61;
	for (int i = 0; i <= 60; ++i) {
		add_edge(start + i, sink, 0, 0);
	}

	for (auto itr : nr) {
		int ind = itr.second;
		for (int poz = 0; poz <= 60; ++i) {
			int cost = 0;
			for (int i = 1; i <= n; ++i) {
				cost += abs(poz - where[i][ind]);
			}
			add_edge(ind, start + poz, 1, cost);
	   	}
	}
}

int main() {
	int t; fin >> t;
 	while (t--) {
		int n; fin >> n;

		nrEl = 0;
		nr.clear();

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= 60; ++j) {
				where[i][j] = 0;
			}
		}

		for (int i = 1; i <= n; ++i) {
			fin >> txt[i];
			vector<int> ap(26, 0);
			int ind = 1;
			for (auto itr : txt) {
				ap[itr - 'a']++;
                if (nr[make_pair(itr, ap[itr - 'a'])] == 0) {
					nr[make_pair(itr, ap[itr - 'a'])] = ++nrEl;
				}
				where[i][nr[make_pair(itr, ap[itr - 'a'])]] = ind;
				++ind;
			}
		}
		


		int mn = inf;

		for (int i = 0; i <= 60; ++i) {
			makeEdges(i);
            get_flow();
		}
	}
	while (get_flow())
		;
	cout << flow_cost << "\n";
	return 0;
}
