#include <fstream>
#include <vector>
using namespace std;

const int kMaxN = 100005;

ifstream in("disjoint.in");
ofstream out("disjoint.out");

int father[kMaxN];
vector<int> children[kMaxN];

void unite(int a, int b) {
	if (children[b].size() > children[a].size()) {
		swap(a, b);
	}

	for (auto itr : children[b]) {
		father[itr] = a;
		children[a].push_back(itr);
	}
	children[b].erase(children[b].begin(), children[b].end());
}

int main() {
	int n, m; in >> n >> m;
    for (int i = 1; i <= n; ++i) {
		father[i] = i;
		children[i].push_back(i);
	}

	while (m--) {
		int t; in >> t;
		if (t == 1) {
	 		int x, y; in >> x >> y;
			unite(father[x], father[y]);
		} else {
			int x, y; in >> x >> y;
			out << ((father[x] == father[y]) ? ("DA") : ("NU")) << '\n';
		}
	}

	in.close();
	out.close();
	return 0;
}
