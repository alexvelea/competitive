#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int max_n = 4005;	

ifstream in("intfm.in");
ofstream out("intfm.out");

int best[max_n], n, x[max_n], y[max_n], poz[max_n];
vector<int> unic;

struct spectacol {
	int st, dr, inside, l, x;
	spectacol (int _st, int _dr) {
		l = _dr - _st;
		x = _st;
		st = lower_bound(unic.begin(), unic.end(), _st) - unic.begin() + 1;
		dr = lower_bound(unic.begin(), unic.end(), _dr) - unic.begin() + 1;
		inside = 1;
	}
	bool operator < (const spectacol &rh) const {
		return st < rh.st;
	}
} ;
vector <spectacol> ord;

bool l_sort (int a, int b) {
	return ord[a].l < ord[b].l;
}

int solve (int st, int dr) {
	for (int i = st; i <= dr; ++i) {
		best[i] = 0;
	}
	int ind = 0;
 	for (int i = st; i <= dr; ++i) {
		best[i] = max(best[i], best[i-1]);
		while (ind < n && ord[ind].st <= i) {
			if (ord[ind].st >= st && ord[ind].dr <= dr)
				best[ord[ind].dr] = max (best[ord[ind].dr], best[i] + ord[ind].inside);
			++ind;
		}
	}
	return best[dr];
}

int main() {
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> x[i] >> y[i];
		unic.push_back(x[i]);
		unic.push_back(y[i]);
	}
	sort(unic.begin(), unic.end());
	unic.resize(unique(unic.begin(), unic.end()) - unic.begin());
	for (int i = 1; i <= n; ++i) 
		ord.push_back(spectacol(x[i], y[i]));
	sort (ord.begin(), ord.end());
	for (int i = 1; i <= n; ++i)
		poz[i] = i - 1;
	sort(poz + 1, poz + n + 1, l_sort);
	for (int i = 1; i <= n; ++i) {
		int x = ord[poz[i]].l / 5;
		ord[poz[i]].inside += solve(
			lower_bound(unic.begin(), unic.end(), ord[poz[i]].x + 2*x) - unic.begin() + 1,
			lower_bound(unic.begin(), unic.end(), ord[poz[i]].x + 3*x + 1) - unic.begin());
	}
	out << solve(1, int(unic.size()));
	return 0;
}

