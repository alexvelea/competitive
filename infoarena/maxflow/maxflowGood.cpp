#include <fstream>
#include <iostream>
#include <vector>

#include <cassert>
#include <ctime>
#include <cstdlib>
using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

struct Edge {
	int a, b, flow, cap;
	Edge() {
		a = b = flow = cap = 0;
	}
	Edge(int _a, int _b, int _cap) {
		a = _a;
		b = _b;
		cap = _cap;
	}

	int other(int _nod) {
		return a + b - _nod;
	}

	int getMaxFlow(int _nod) {
		if (_nod == a) {
			return cap - flow;
		} else {
			return flow;
		}
	}
	
	int getReverseMaxFlow(int _nod) {
		return getMaxFlow(other(_nod));
	}

	void pumpFlow(int _nod, int _f) {
		if (_nod == a) {
			flow += _f;
		} else {
			flow -= _f;
		}
	}

	void pumpReverseFlow(int _nod, int _f) {
		pumpFlow(other(_nod), _f);
	}
};

struct Flow {
	static int inf;
	int source, sink, flow, maxNod;
	vector<vector<int> > edgeId;
	vector<Edge> edges;

	Flow() {
		source = sink = flow = maxNod = 0;	
		edgeId.resize(1);
	}
	
	Flow(int _source, int _sink, int _maxNod) {
		source = _source;
		sink = _sink;
        maxNod = _maxNod;
		edgeId.resize(maxNod + 1);
		flow = 0;
	}

	void addEdge(int a, int b, int cap) {
		assert(a <= maxNod and b <= maxNod);
 		edgeId[a].push_back(edges.size());
 		edgeId[b].push_back(edges.size());
		edges.push_back(Edge(a, b, cap));
	}

	int pumpFlow() {
		const int notVisited = -1;
		vector<int> father(maxNod + 1, notVisited), que(maxNod + 1, 0);
		que.clear();
 		
		father[source] = source;
		que.push_back(source);

		srand(time(NULL));
		while (que.size() and father[sink] == notVisited) {
			int ind = rand() % que.size();
			int nod = que[ind];
			que[ind] = que[que.size() - 1]; que.pop_back();
			for (auto itr : edgeId[nod]) {
				if (father[edges[itr].other(nod)] == notVisited and edges[itr].getMaxFlow(nod)) {
					father[edges[itr].other(nod)] = itr;
					que.push_back(edges[itr].other(nod));
				}
			}
		}

		if (father[sink] == notVisited) {
			return 0;
		}
			
		int mxFlow = inf;
		for (int nod = sink; nod != source; nod = edges[father[nod]].other(nod)) {
 			mxFlow = min(mxFlow, edges[father[nod]].getReverseMaxFlow(nod));
		}

		for (int nod = sink; nod != source; nod = edges[father[nod]].other(nod)) {
			edges[father[nod]].pumpReverseFlow(nod, mxFlow);
		}

		return mxFlow;
	}

	int getFlow() {
		int actFlow = 0;
		do {
			actFlow = pumpFlow();
			flow += actFlow;
		} while (actFlow != 0);
		return flow;
	}
} flow;

int Flow::inf = 0x3f3f3f3f;

int main() {
 	int n, m; fin >> n >> m;
	flow = Flow(1, n, n);
	while (m--) {
		int a, b, f; fin >> a >> b >> f;
		flow.addEdge(a, b, f);
	}
	fout << flow.getFlow() << '\n';
	return 0;
}
