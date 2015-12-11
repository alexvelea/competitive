// 8:31
#include <cassert>
#include <ctime>

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream in ("maxflow.in");
ofstream out ("maxflow.out");

const int max_n = 1005;
vector <int> vertex[max_n];
int from[max_n];

int source, sink;
int max_flow;

void get_min(int &a, int b) {
	if (a > b)
		a = b;
}

struct muchie {
	int a, b, c, f;
	muchie() {
		a = b = c = f = 0;
	}
	muchie(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
		f = 0;
	}
	int other(int nod) {
		return a + b - nod;
	}
	int cap(int nod) {
		if (nod == a)
			return c-f;
		return f;
	}
 	int back_cap(int nod) {
		return cap (a + b - nod);
	}
	void set_flow(int nod, int val) {
		if (nod == a) {
			assert (f + val <= c);
			f += val;
		} else {
			assert (f >= val);
			f -= val;
		}
	}
	void set_back_flow(int nod, int val) {
		set_flow (a + b - nod, val);
	}
} edge[5005];
int nr_edge;

void add_edge(int a, int b, int c) {
	++nr_edge;
    edge[nr_edge] = muchie (a, b, c);
	vertex[a].push_back (nr_edge);
	vertex[b].push_back (nr_edge);
}

int que[max_n];

void clear_flow(){
	for (int i = 0; i < max_n; ++i)
		from[i] = 0;
}

bool get_flow() {
	clear_flow();
	int dr = 0;
	que[dr] = source;
	from[source] = source;
	while (dr >= 0) {
		if (from[sink])
			break;
		int ind = rand() % (dr+1);
		int nod = que[ind];
		que[ind] = que[dr--];
		for (vector<int> :: iterator it = vertex[nod].begin(); it != vertex[nod].end(); ++it) {
			int other = edge[*it].other (nod);
			if (edge[*it].cap(nod) > 0 && !from[other]) {
				from[other] = *it;
				que[++dr] = other;
			}
		}
	}
	if (!from[sink])
		return false;
	int mx = 0x3f3f3f3f;
	for (int nod = sink; nod != source; nod = edge[from[nod]].other(nod))
		get_min (mx, edge[from[nod]].back_cap (nod));
	for (int nod = sink; nod != source; nod = edge[from[nod]].other(nod))
		edge[from[nod]].set_back_flow (nod, mx);
	max_flow += mx;
	return true;
}

int main() {
	srand(time(NULL));
	int n, m;
	in >> n >> m;
	source = 1;
	sink = n;
	while (m--) {
		int a, b, c;
		in >> a >> b >> c;
		add_edge (a, b, c);
	}
	while (get_flow())
		;
	out << max_flow << "\n";
	return 0;
}
