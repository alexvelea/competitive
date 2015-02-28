#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

ifstream in("count.in");
ofstream out("count.out");
#define FORIT(st, i, v) for(int i = st; i < int(v.size()); ++i)
const int max_n = 30005;

vector<int> vertex[max_n], v;
priority_queue <pair<int,int> > pq;
unordered_map <int,bool> mu[max_n];

int n, m;
bool viz[max_n];
int sz[max_n];
int rez[5];

void bt (int nod) {
 	FORIT(0, it, v)
		FORIT(it+1, it2, v) {
			int a = nod, b = v[it], c = v[it2];
			if (mu[a][b] && mu[b][c] && mu[c][a]) {
				rez[3] ++;
				FORIT (it2+1, it3, v) {
					int d = v[it3];
					if (mu[a][d] && mu[d][b] && mu[d][c])
						rez[4]++;
				}
			}
		}
}

int main() {
 	in >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b;
		in >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
		mu[a][b] = true;
		mu[b][a] = true;
	}
	for (int i = 1; i <= n; ++i) {
		pq.push (make_pair(-vertex[i].size(), i));
		sz[i] = vertex[i].size();
	}
	while (pq.size()) {
   		int nod = pq.top().second;
		pq.pop();
		if (viz[nod])
			continue ;
		viz[nod] = true;
		v.clear();
		FORIT (0, it, vertex[nod])
			if (not viz[vertex[nod][it]])
				v.push_back(vertex[nod][it]);
		bt(nod);
		FORIT (0, it, vertex[nod]) {
			int a = vertex[nod][it];
 			sz[a] --;
			pq.push(make_pair(-sz[a], a));
		}
	} 
	rez[2] = m;
	for (int i = 4; i; --i)
		if (rez[i]) {
			out << i << ' ' << rez[i] << '\n';
			return 0;
		}
	return 0;
}
