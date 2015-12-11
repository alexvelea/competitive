#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define FORIT(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

ifstream in("island.in");
ofstream out("island.out");

const int max_n = 1000005;

queue<int> que;
vector<pair<int, int> > vertex[max_n];
pair<int, int> next[max_n];
int viz[max_n];
int start;

void df(int nod) {
	que.push(nod);
	viz[nod] = viz[0];
	if (viz[next[nod].fi] == viz[0]) {
		// find cicle;
		start = next[nod].fi;
		return ;
	}
	if (viz[next[nod].fi])
		return ;
	df(next[nod].fi);
}

void get_cicle (int nod) {
	while (que.front() != nod)
		que.pop();
	while (que.size()) {
		cerr << que.front() << ' ';
		que.pop();
	}
	cerr << '\n';
}

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int b, l;
		in >> b >> l;
		next[i] = mp(b, l);
 		vertex[i].pb(mp(b, l));
		vertex[b].pb(mp(i, l));
	}
	for (int i = 1; i <= n; ++i)
		if (not viz[i]) {
			while (que.size())
				que.pop();
			++viz[0];
			start = 0;
			df(i);
			if (start != 0)
				get_cicle(start);
		}
	return 0;
}

