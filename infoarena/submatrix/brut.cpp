#include <fstream>
#include <iostream>
using namespace std;

ifstream in("submatrix.in");
ofstream out("submatrix2.out");

const int kMaxN = 300;

int el[kMaxN][kMaxN];
int ap[kMaxN * kMaxN];
int mx, n, m, k, rez = 0;

int main() {
    in >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			in >> el[i][j];
			if (mx < el[i][j])
				mx = el[i][j];
		}

	int C, L;

	for (int l = 1; l <= n; ++l)
		for (int c = 1; c <= m; ++c) {
            int inside = 0;
			for (int i = 0; i <= mx; ++i)
				ap[i] = 0;

			for (int d = 0; l + d <= n and c + d <= m; ++d) {
				for (int i = l; i <= l + d; ++i) {
					int e = el[i][c + d];
					if (ap[e] == 0)
						inside++;
					ap[e]++;
				}
				for (int j = c; j < c + d; ++j) {
					int e = el[l + d][j];
					if (ap[e] == 0)
						inside++;
					ap[e]++;
				}
				if (inside <= k) {
					if (rez < d) {
						rez = d;
						C = c;
						L = l;
					}
				}
			}
		}
//	cerr << L << '\t' << C << '\n';
	out << rez + 1;
	in.close();
	out.close();
	return 0;
}
