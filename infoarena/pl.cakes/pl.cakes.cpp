//Problem pl.cakes from Infoarena
// "We are drowning in information and starved for knowledge."
#include <algorithm>
#include <fstream>
//#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream cin("cia10a.in");
//ifstream cin("pl.cakes.in"); 
ofstream cout("pl.cakes.out");

int flour[kMaxN];
bool viz[kMaxN];

unordered_map<int, bool> edge[kMaxN];
pair<int, int> vertex_size[kMaxN];
vector<int> vertex[kMaxN];

set<pair<int, int> > sz;
int siz[kMaxN];

int main() {
	int n, m;
	cin >> n >> m;
	
    for (int i = 1; i <= n; ++i)
		cin >> flour[i];

	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		vertex[a].push_back(b);
		vertex[b].push_back(a);
		edge[a][b] = edge[b][a] = true;
	}

	for (int i = 1; i <= n; ++i) {
//		siz[i] = vertex[i].size();
//		sz.insert(make_pair(siz[i], i));
		vertex_size[i] = make_pair(vertex[i].size(), i);
	}
	sort(vertex_size + 1, vertex_size + n + 1);

	int64 rez = 0;

	for (int i = 1; i <= n; ++i) {
		int nod = vertex_size[i].second;
		viz[nod] = true;
//		for (int a = 0; a < int(vertex[nod].size()); ++a) 
//			if (viz[vertex[nod][a]] == true) {
//				vertex[nod][a] = vertex[nod].back();
//				vertex[nod].pop_back();
//				--a;
//			}

		for (int a = 0; a < int(vertex[nod].size()); ++a) {
			int A = vertex[nod][a];
			if (viz[A] == true)
				continue;
			for (int b = a + 1; b < int(vertex[nod].size()); ++b) {
				int B = vertex[nod][b];
				if (viz[B] == true)
					continue;
				if (edge[A][B]) {
					int mx = max(flour[A], flour[B]);
					mx = max(mx, flour[nod]);
					rez += mx;
//					cout << nod << '\t' << A << '\t' << B << '\n';
				}
			}
		}
		
/*		for (int i = 0; i < int(vertex[nod].size()); ++i) {
			int n = vertex[nod][i];
			if (viz[n] == false) {
				sz.erase(sz.find(make_pair(siz[n], n)));
				siz[n]--;
				sz.insert(make_pair(siz[n], n));
			}
		}*/
	}
 	cout << rez << '\n';
	return 0;
}
