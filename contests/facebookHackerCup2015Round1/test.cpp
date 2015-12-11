#include <iostream>
using namespace std;

int main() {
 		int sz = 3, x, itr = 0, inf = 1000, global[100], start[1], sol[100];
		for (int i = 0; i < 100; ++i)
			sol[i] = 0;


		cin >> x;
		for (int i = 0; i < x; ++i)
			cin >> global[i];
		start[0] = 0;

		int st[x + 1], dr[x + 1];
		st[0] = inf;
		dr[x - 1] = inf;
		for (int i = 1; i <= x; ++i) {
			st[i] = min(st[i - 1], global[start[itr] + i - 1]);
		}
		for (int i = x - 2; i >= 0; --i) {
			dr[i] = min(dr[i + 1], global[start[itr] + i + 1]);
		}
        for (int i = 0; i <= x; ++i)
			cerr << st[i] << '\t';
		cerr << '\n';
		for (int i = 0; i <= x; ++i)
			cerr << dr[i] << '\t';
		cerr << '\n';

		for (int i = 0; i < x; ++i) {
			if (i < sz) {
				sol[i] += min(st[i], dr[i]);
			}
			if (i + 1 < sz) {
				sol[i + 1] -= min(st[i], dr[i]);
			}
		}
		if (x < sz)
			sol[x] += st[x];    

		for (int i = 1; i < 100; ++i)
			sol[i] += sol[i - 1];

		for (int i = 0; i < sz; ++i)
			cerr << sol[i] << '\n';
}
