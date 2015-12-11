#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> vertex[1005];
queue<int> q;

int best[1005], viz[1005];
int r[1005], c[1005];

int main() {
	ifstream in("adriatic.in");
	ofstream out("adriatic2.out");
	int m;
	in >> m;
	for (int i = 1; i <= m; ++i)
		in >> r[i] >> c[i];
	for (int i = 1; i <= m; ++i) 
		for (int j = 1; j <= m; ++j)
			if (r[i] > r[j] && c[i] > c[j]) {
				vertex[i].push_back(j);
				vertex[j].push_back(i);
			}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			best[j] = 1005;
			viz[j] = false;
		}
		best[i] = 0;
		viz[i] = true;
		q.push(i);
		while (q.size()) {
			int nod = q.front();
			q.pop();
			for (int j = 0; j < int(vertex[nod].size()); ++j) {
				int act = vertex[nod][j];
				if (not viz[act]) {
					viz[act] = true;
					best[act] = best[nod] + 1;
					q.push(act);
				}
			}
		}
		int rez = 0;
		for (int j = 1; j <= m; ++j)
			rez += best[j];
		out << rez << '\n';
	}
}
