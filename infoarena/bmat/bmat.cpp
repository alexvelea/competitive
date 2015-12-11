#include <fstream>
#include <iostream>
using namespace std;

const int max_n = 1005, MOD = 666013;
ifstream in("bmat.in");
ofstream out("bmat.out");

int X[max_n][max_n], S[max_n][max_n];
int n, m, k;

int main() {
	in >> n >> m >> k;
	X[n][m] = 0;
	for (int i = n; i; --i)
		for (int j = m; j; --j) {
 			S[i][j] = S[i+1][j] ^ S[i+1][j+1] ^ S[i][j+1];
			X[i][j] ^= S[i][j];
			if (i + k < max_n)
				X[i][j] ^= S[i + k][j];
			if (i + k < max_n && j + k < max_n)
				X[i][j] ^= S[i + k][j + k];
			if (j + k < max_n)
				X[i][j] ^= S[i][j + k];
			X[i][j] ^= 1;
			S[i][j] ^= X[i][j];
   	}
//	for (int i = 1; i <= n; ++i, cout << '\n')
//		for (int j = 1; j <= m; ++j)
//			cout << X[i][j] << ' ';
	int x = 0, r[2];
	r[1] = r[0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			char el;
			in >> el;
			if (el == '1')
				x ^= X[i][j];
			if (el == '?') {
				r[X[i][j]]++;
			}
		}
	int d = 1, u = 1;
	for (int i = 1; i <= r[0]; ++i) {
		d *= 2;
		if (d >= MOD)
			d -= MOD;
	}
	if (r[1] == 0) {
		if (x == 0)
			d = 0;
	} else {
		for (int i = 1; i < r[1]; ++i) {
			u *= 2;
			if (u >= MOD)
				u -= MOD;
		}
	}
	out << (1LL * u * d) % MOD << '\n';
	return 0;
}
