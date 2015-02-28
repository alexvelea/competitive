#include <algorithm>
#include <fstream>
//#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

const int vertexLimit = 650, kMaxN = 100005;

int flour[kMaxN];
vector<int> vertex[kMaxN];
vector<pair<int, int> > query[kMaxN];
bool vertexType[kMaxN];

int64 rez = 0;

ifstream cin("cia10a.in");
ofstream cout("pl.cakes2.out");

void querySolve(int nod) {
	sort(vertex[nod].begin(), vertex[nod].end());
	sort(query[nod].begin(), query[nod].end());

	for (int a = 0, b = 0; a < int(vertex[nod].size()) and b < int(query[nod].size()); ++a) {
		while (b < int(query[nod].size()) and query[nod][b].first <= vertex[nod][a]) {
			if (query[nod][b].first == vertex[nod][a]) {
				rez += max(max(flour[nod], flour[vertex[nod][a]]), query[nod][b].second);
			}
			++b;
		}
	}

	return ;
}

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
	}	

	for (int i = 1; i <= n; ++i) {
		vertexType[i] = (vertex[i].size() >= vertexLimit);
	}

 	for (int i = 1; i <= n; ++i) {
		if (vertexType[i])
			continue;
		querySolve(i);
 		for (int a : vertex[i])
			for (int b : vertex[i])
				if (i < a and a < b) {
					query[a].push_back(make_pair(b, flour[i]));
				}
	}
	
	for (int i = 1; i <= n; ++i) {
		if (not vertexType[i])
			continue;
		querySolve(i);
  		for (int a : vertex[i]) {
			if (vertexType[a] == true)
				for (int b : vertex[i])
					if (i < a and a < b and vertexType[b] == true) {
						query[a].push_back(make_pair(b, flour[i]));
					}   	
		}
	}

	cout << rez << '\n';
	return 0;
}

