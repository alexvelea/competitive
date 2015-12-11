#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("fotbal2.in");
ofstream out("fotbal2.out");

const int kMaxN = 50005;

int viz_m[kMaxN * 2], itr_m[kMaxN];
pair<int, int> edge[kMaxN * 2];
int win[kMaxN * 2];

vector<int> vertex[kMaxN];

void euler(int nod) {
	for (; itr_m[nod] < int(vertex[nod].size());) {
		int edg = vertex[nod][itr_m[nod]];
		++itr_m[nod];
		if (viz_m[edg] == true)
 			continue;
		viz_m[edg] = true;
		int oth = edge[edg].first + edge[edg].second - nod;
		win[edg] = nod;
		euler(oth);
	}
}

int main() {
	int n, m;
	in >> n >> m;
 	for (int i = 1; i <= m; ++i) {
    	int a, b;
		in >> a >> b;
		edge[i] = make_pair(a, b);
		vertex[a].push_back(i);
		vertex[b].push_back(i);
	}
	int cm = m + 1;
	for (int i = 1; i <= n; ++i)
		if (vertex[i].size() % 2 == 1) {
			int st = i;
			for (i++; i <= n and vertex[i].size() % 2 == 0; i++)
				;
 			int dr = i;
            edge[cm] = make_pair(st, dr);
			vertex[st].push_back(cm);
			vertex[dr].push_back(cm);
			++cm;
		}

	for (int i = 1; i <= n; ++i)
		if (itr_m[i] < int(vertex[i].size()))
			euler(i);
	if (cm == m + 1)
		out << "0\n";
	else
		out << "2\n";
	for (int i = 1; i <= m; ++i)
		out << win[i] << '\n';
	in.close();
	out.close();
	return 0;
}

