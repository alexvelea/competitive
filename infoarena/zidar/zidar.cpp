//Problem zidar from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 51, kMaxM = 21, kMaxX = 61;

ifstream in("zidar.in");
ofstream out("zidar.out");

int sum[kMaxN][kMaxM];
int best[kMaxN][kMaxM][kMaxM][kMaxX];
int el[kMaxN][kMaxM];


int Sum(int l, int st, int dr) {
	return sum[l][dr] - sum[l][st - 1] + sum[l - 1][st - 1] - sum[l - 1][dr];
}

void get_min(int &a, int b) {
	if (a > b)
		a = b;
}

int main() {
	int m, n, c, x;
	in >> n >> m >> x >> c;
    for (int i = n; i; --i)
		for (int j = 1; j <= m; ++j)
			in >> el[i][j];

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + el[i][j];

 	for (int l = 1; l <= n; ++l)
		for (int st = 1; st <= m; ++st)
			for (int dr = 1; dr <= m; ++dr)
				for (int el = 0; el < kMaxX; ++el)
					best[l][st][dr][el] = inf;
	
	for (int st = 1; st <= m; ++st)
		for (int dr = st; dr <= m; ++dr) {
			best[n][st][dr][dr - st + 1] = Sum(n, st, dr);
		}
	for (int l = n - 1; l; --l) {
/*         if (l == n - 2)
			for (int poz = 1; poz <= m; ++poz)
				for (int L = 1; L <= m; ++L)
					cerr << poz << '\t' << L << '\t' << best[l + 1][poz][L][5] << '\n'; */

		for (int el = 0; el <= x; ++el)
			for (int L = m; L > 1; --L)
				for (int st = 1, dr = L; dr <= m; ++st, ++dr) {
					get_min(best[l + 1][st + 1][dr][el], best[l + 1][st][dr][el]);
					get_min(best[l + 1][st][dr - 1][el], best[l + 1][st][dr][el]);
				}



		for (int nr = 0; nr <= x; ++nr)
			for (int L = 1; L <= m and L <= nr; ++L) 
				for (int st = 1, dr = L; dr <= m; ++st, ++dr) {
					get_min(best[l][st][dr][nr], best[l + 1][dr][dr][nr - (dr - st + 1)] + Sum(l, st, dr));
					if (st != dr)
						get_min(best[l][st][dr][nr], best[l][st][dr - 1][nr - 1] + el[l][dr]);
				}
	}

	int rez = 0;
	for (int l = 1; l <= n; ++l)
		for (int st = 1; st <= m; ++st)
			for (int dr = 1; dr <= m; ++dr)
				for (int el = 1; el <= x; ++el)
					if (best[l][st][dr][el] <= c and el >= rez)
						rez = el;

	out << rez << '\n';
	return 0;
}
