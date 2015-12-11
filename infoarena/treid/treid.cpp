#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("treid.in");
ofstream out("treid.out");

const int inf = 0x3f3f3f3f, kMaxN = 205;
int n, m;
int el[kMaxN][kMaxN];

void rotate() {
	int aux[kMaxN][kMaxN];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			aux[m - j + 1][i] = el[i][j];
		}
	swap(n, m);
	for (int i = 0; i <= n + 1; ++i) {
		el[i][0] = 0;
		el[i][m + 1] = 0;
	}
	for (int j = 0; j <= m + 1; ++j) {
		el[0][j] = 0;
		el[n + 1][j] = 0;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			el[i][j] = aux[i][j];
	return ;
}

int dplin[kMaxN][kMaxN];
pair<int, int> dpcol[kMaxN][kMaxN];
int sum[kMaxN][kMaxN];

int solve() {
	int mx = -inf;
	// make them dp-s
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + el[i][j];

	for (int up = 1; up <= n; ++up)
		for (int down = up; down <= n; ++down) {
			int mn = 0;
			int s = 0;
			int rez = -inf;
			for (int c = 1; c <= m; ++c) {
				s = sum[down][c] - sum[up - 1][c];
				rez = max(rez, s - mn);
				mn = min(mn, s);
			}
			dplin[up][down] = rez;
		}

	for (int l = 2; l <= n; ++l)
		for (int st = 1; st + l - 1 <= n; ++st) {
			int dr = st + l - 1;
 			dplin[st][dr] = max(dplin[st][dr], max(dplin[st][dr - 1], dplin[st + 1][dr]));
		}

	for (int a = 1; a <= n; ++a)
		for (int b = a + 1; b < n; ++b) {
			int rez = dplin[1][a] + dplin[a + 1][b] + dplin[b + 1][n];
			mx = max(mx, rez);
		}
	
    for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j) {
			dpcol[i][j].first = -inf;
			dpcol[i][j].second = 0;
		}

	for (int l = 1; l < n; ++l) {
		for (int st = 1; st <= m; ++st)
			for (int dr = st; dr <= m; ++dr) {
				int s = sum[l][dr] - sum[l][st - 1];
				dpcol[st][dr].first = max(dpcol[st][dr].first, s - dpcol[st][dr].second);
				dpcol[st][dr].second = min(dpcol[st][dr].second, s);
			}
		for (int l = 2; l <= m; ++l)
			for (int st = 1, dr = l; dr <= m; ++st, ++dr)
				dpcol[st][dr].first = max(dpcol[st][dr].first, max(dpcol[st + 1][dr].first, dpcol[st][dr - 1].first));
		for (int st = 1; st < m; ++st) {
				int rez = dpcol[1][st].first + dpcol[st + 1][m].first + dplin[l + 1][n];
				mx = max(mx, rez);
			}
	}

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j) {
			dpcol[i][j].first = -inf;
			dpcol[i][j].second = 0;
		}

 	for (int l = n; l > 1; --l) {
		for (int st = 1; st <= m; ++st)
			for (int dr = st; dr <= m; ++dr) {
				int s = sum[n][dr] - sum[n][st - 1] - sum[l - 1][dr] + sum[l - 1][st - 1];
				dpcol[st][dr].first = max(dpcol[st][dr].first, s - dpcol[st][dr].second);
				dpcol[st][dr].second = min(dpcol[st][dr].second, s);
			}
		for (int l = 2; l <= m; ++l)
			for (int st = 1, dr = l; dr <= m; ++st, ++dr)
				dpcol[st][dr].first = max(dpcol[st][dr].first, max(dpcol[st + 1][dr].first, dpcol[st][dr - 1].first));
		for (int st = 1; st < m; ++st) {
				int rez = dpcol[1][st].first + dpcol[st + 1][m].first + dplin[1][l - 1];
				mx = max(mx, rez);
			}
	}   	
	return mx;
}


int main() {
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			in >> el[i][j];
	
	int mx = -inf;
	for (int d = 0; d < 2; ++d) {
		mx = max(mx, solve());
		rotate();
	} 
	out << mx << '\n';

	in.close();
	out.close();
    return 0;
}
