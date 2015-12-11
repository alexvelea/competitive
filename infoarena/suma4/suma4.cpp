#include <fstream>
#include <iostream>
using namespace std;

ifstream in("suma4.in");
ofstream out("suma4.out");

const int kMaxN = 60, kInf = 100005;
const int dx[4] = {0, 0, 1, 1};
const int dy[4] = {0, 1, 0, 1};

int el[kMaxN][kMaxN][kMaxN];
int best[kMaxN][kMaxN][kMaxN], from[kMaxN][kMaxN][kMaxN];

int main() {
	int n;
	in >> n;
	int nr_el = 0;
	int lev = 0;
	for (lev = 1; nr_el < n; ++lev)
		for (int i = 1; i <= lev; ++i)
			for (int j = 1; j <= lev; ++j) {
				++nr_el;
				in >> el[lev][i][j];
			}
	--lev;
	for (int i = 1; i <= lev; ++i)
		for (int j = 1; j <= lev; ++j)
			best[lev][i][j] = el[lev][i][j];
	for (int l = lev - 1; l; --l)
		for (int i = 1; i <= l; ++i)
			for (int j = 1; j <= l; ++j) {
				best[l][i][j] = kInf;
				for (int d = 0; d < 4; ++d) {
					if (best[l][i][j] > best[l + 1][i + dx[d]][j + dy[d]]) {
						best[l][i][j] = best[l + 1][i + dx[d]][j + dy[d]];
						from[l][i][j] = d;
					}
				}
				best[l][i][j] += el[l][i][j];
			}
 	out << lev << ' ' << best[1][1][1] << '\n';
	int x = 1, y = 1;
	int base = 1;
	for (int l = 1; l <= lev; base += l * l, l++) {
		out << base + y + l * (x - 1) - 1 << ' ';
		int nx = dx[from[l][x][y]] + x;
		int ny = dy[from[l][x][y]] + y;
		x = nx;
		y = ny;
	}
	return 0;
}
