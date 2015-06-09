//Problem d from googleCodeJam2015QualificationRound
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

map<pair<int, pair<int, int> > , bool> Bad;

int main() {
	ios::sync_with_stdio(false);
	Bad = {
{{1, {3, 3}}, true},
{{1, {6, 3}}, true},
{{1, {9, 3}}, true},
{{1, {12, 3}}, true},
{{1, {15, 3}}, true},
{{1, {18, 3}}, true},
{{1, {4, 4}}, true},
{{1, {8, 4}}, true},
{{1, {12, 4}}, true},
{{1, {16, 4}}, true},
{{1, {20, 4}}, true},
{{2, {2, 4}}, true},
{{2, {4, 4}}, true},
{{2, {6, 4}}, true},
{{2, {8, 4}}, true},
{{2, {10, 4}}, true},
{{2, {12, 4}}, true},
{{2, {14, 4}}, true},
{{2, {16, 4}}, true},
{{2, {18, 4}}, true},
{{2, {20, 4}}, true},
{{1, {5, 5}}, true},
{{1, {10, 5}}, true},
{{1, {15, 5}}, true},
{{1, {20, 5}}, true},
{{2, {5, 5}}, true},
{{2, {10, 5}}, true},
{{2, {15, 5}}, true},
{{2, {20, 5}}, true},
{{1, {6, 6}}, true},
{{1, {12, 6}}, true},
{{1, {18, 6}}, true},
{{2, {3, 6}}, true},
{{2, {6, 6}}, true},
{{2, {9, 6}}, true},
{{2, {12, 6}}, true},
{{2, {15, 6}}, true},
{{2, {18, 6}}, true},
{{3, {4, 6}}, true},
{{3, {6, 6}}, true},
{{3, {8, 6}}, true},
{{3, {10, 6}}, true},
{{3, {12, 6}}, true},
{{3, {14, 6}}, true},
{{3, {16, 6}}, true},
{{3, {18, 6}}, true},
{{3, {20, 6}}, true},   	
	};

	ifstream fin("d.in");
	ofstream fout("d.out");

    int t; fin >> t;
	for (int T = 1; T <= t; ++T) {
		int x, n, m; fin >> x >> n >> m;
		if (n > m) {
			swap(n, m);
		}
 		bool ok = true;
		if (Bad[make_pair(n, make_pair(m, x))]) {
			ok = false;
		}
		if (n * m % x != 0)
			ok = false;
		if (x >= 7) {
			ok = false;
		}

		fout << "Case #" << T << ": " << (ok ? ("GABRIEL") : ("RICHARD")) << '\n';
	}
	return 0;
}
