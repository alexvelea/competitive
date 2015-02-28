#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> vertex[50];
pair<int, int> edge[50];

ifstream in("radare.in");
ofstream out("radare2.out");

int cost[50];
int viz[50];

int df(int nod, int st) {
	int rez = 0;
	viz[nod] = true;
	for (int i = 0; i < int(vertex[nod].size()); ++i)
		if (st & (1 << (vertex[nod][i]))) {
			int e = vertex[nod][i];
			int oth = edge[e].first + edge[e].second - nod;
			if (viz[oth] == false)
				rez += df(oth, st);
		}
	rez += cost[nod];
	return rez;
}

int main() {
	int n, p;
	in >> n >> p;
	for (int i = 1; i < n; ++i) {
		int a, b;
		in >> a >> b;
    	edge[i - 1] = make_pair(a, b);
		vertex[a].push_back(i - 1);
		vertex[b].push_back(i - 1);
	}
	for (int i = 1; i <= n; ++i)
		in >> cost[i];

	int rez = 0;
	for (int i = 0; i < int(1 << (n - 1)); ++i) {
		for (int j = 1; j <= n; ++j)
			viz[j] = 0;
		if (df(1, i) == p)
			++rez;
	}
	out << rez % 31333 << '\n';
	in.close();
 	out.close();
	return 0;
}
