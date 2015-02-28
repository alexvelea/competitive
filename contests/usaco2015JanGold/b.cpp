//Problem B from Codeforces Round usaco2015JanGold
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 21, kMaxEl = 1005;

ifstream in("movie.in");
ofstream out("movie.out");

int n[kMaxEl], d[kMaxEl];

int el[kMaxN][kMaxEl];
int _right[kMaxN][kMaxEl];

int best[1 << kMaxN];

int main() {
	int l, N;
	in >> N >> l;
	for (int i = 0; i < N; ++i) {
		in >> d[i] >> n[i];
		for (int j = 1; j <= n[i]; ++j) {
			in >> el[i][j];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = n[i]; j; --j) {
			int dr = j;
			while (dr <= n[i] and el[i][dr] < el[i][j] + d[i])
				++dr;
			if (el[i][dr] == el[i][j] + d[i])
                _right[i][j] = _right[i][dr];
			_right[i][j] += d[i];
		}
		int mx = 0;
		for (int j = 1; j <= n[i]; ++j) {
			mx = max(_right[i][j] + el[i][j], mx);
			_right[i][j] = el[i][j] + d[i];
		}
	}

	for (int st = 1; st < (1 << N); ++st) {
		// de unde vine starea st;
		for (int i = 0; i < N; ++i) {
			if ((1 << i) & st) {
		 		// poate sa vina de aici
				int target = best[st ^ (1 << i)];
				int l = 0;
				for (int p = 1 << 10; p; p /= 2) {
					if (l + p <= n[i]) {
						if (el[i][l + p] <= target) {
							l += p;
						}
					}
				}
				best[st] = max(best[st], _right[i][l]);
			}
		}
	}

	int mn = inf;
	for (int st = 1; st < (1 << N); ++st) {
//		cerr << st << '\t' << best[st] << '\n';
		if (best[st] >= l) {
			int aux = st, nr = 0;
			while (aux) {
				nr++;
				aux -= aux & (-aux);
			}
			mn = min(nr, mn);
		}
	}
 	if (mn == inf)
		mn = -1;
	out << mn << '\n';
	return 0;
}
