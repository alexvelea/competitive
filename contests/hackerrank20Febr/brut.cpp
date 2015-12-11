#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int kMaxN = 10005;

ifstream in("library.in");
ofstream out("library2.out");

int el[kMaxN];

int solve(int st, int dr, int k) {
	vector<int> e;
	for (int i = st; i <= dr; ++i)
		e.push_back(el[i]);
	sort(e.begin(), e.end());
	return e[k - 1];
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, q;
		in >> n;
		for (int i = 1; i <= n; ++i)
			in >> el[i];
		in >> q;
		while (q--) {
			int t;
			in >> t;
			if (t == 0) {
				int st, dr, k;
				in >> st >> dr >> k;
				out << solve(st, dr, k) << '\n';
			} else {
				int x, e;
				in >> x >> e;
				el[x] = e;
			}
		}
	}
	return 0;
}

