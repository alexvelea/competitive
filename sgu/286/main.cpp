#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int max_n = 1000000;
#define FORIT(it,v) for(vector<int> :: iterator it = (v).begin(); it != (v).end(); ++it)

pair<int,int> edge[max_n];
int current_edge[max_n], viz[max_n], father[max_n];
int other[max_n];
vector<int> vertex[max_n];
map<int, int> edge_ind[max_n];

void df (int nod) {
	int &i = current_edge[nod];
	for (; i < int(vertex[nod].size()); ) {
		if (viz[vertex[nod][i]])
			++i;
		else {
			father[vertex[nod][i]] = nod;
			viz[vertex[nod][i]] = true;
			df(edge[vertex[nod][i]].first + edge[vertex[nod][i]].second - nod);
		}
	}
	return ;
}

bool find_match(int nod) {
	viz[nod] = true;
	FORIT(it, vertex[nod]) 
		if (not other[*it]) {
			other[*it] = nod;
			other[nod] = *it;
			return true;
		}
	FORIT(it, vertex[nod])
		if (not viz[other[*it]] && find_match(other[*it])) {
			other[nod] = *it;
			other[*it] = nod;
			return true;
		}
	return false;
}

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n * k / 2; ++i) {
		int a, b;
		cin >> a >> b;
		edge_ind[a][b] = edge_ind[b][a] = i;
 		edge[i] = make_pair(a, b);
		vertex[a].push_back(i);
		vertex[b].push_back(i);
	}
	for (int i = 1; i <= n; ++i)
		if (not current_edge[i])
			df(i);
	for (int i = 1; i <= n; ++i) 
		vertex[i].clear();
	for (int i = 1; i <= n * k / 2; ++i) {
		vertex[father[i]].push_back(n + edge[i].first + edge[i].second - father[i]);
	}
	bool ok;
	for (int i = 1; i <= n; ++i)
		viz[i] = false;
	do {
		ok = false;
		for (int i = 1; i <= n; ++i)
			if (!viz[i] && not other[i] && find_match(i)) 
				ok = true;
		for (int i = 1; i <= n; ++i)
			viz[i] = false;
	} while (ok);
	cout << "YES\n";
	for (int i = 1; i <= n; ++i) {
		cout << edge_ind[i][other[i] - n] << "\n";
	}
	return 0;
}
