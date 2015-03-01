#include <cassert>

#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 100005;

ifstream in;
ofstream out;

int father[kMaxN], deep[kMaxN];

int getFather(int nod) {
	if (father[nod] != nod)
		father[nod] = getFather(father[nod]);
	return father[nod];
}                  

void unite(int a, int b) {
	if (getFather(a) != a or getFather(b) != b or a == b) {
		assert(0);
	}

	if (deep[a] > deep[b]) {
		father[b] = a;
	} else {
		deep[b] = max(deep[b], deep[a] + 1);
		father[a] = b;
	}
}



int main() {
	in.open("disjoint.in");
	int n, m; in >> n >> m;
	for (int i = 1; i <= n; ++i) {
		father[i] = i;
		deep[i] = i;
	}

	out.open("disjoint.out");
	while (m--) {
		int t; in >> t;
		if (t == 1) {
			int x, y; in >> x >> y;
			unite(getFather(x), getFather(y));
		} else {
			int x, y; in >> x >> y;
			out << ((getFather(x) == getFather(y)) ? ("DA") : ("NU")) << '\n';
		}
	}

	in.close();
	out.close();
	return 0;
}
