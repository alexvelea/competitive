//21:25
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 30005, MOD = 997;
ifstream in("namlei.in");
ofstream out("namlei.out");

int n, K, X, Y;
int cnt, i, j, k;

struct Matrice {
	short el[8][8];
	Matrice() {
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				el[i][j] = 0;
		for (int i = 0; i < 8; ++i)
			el[i][i] = 1;
	}
	Matrice (int cnt, int x, int y, int O) {
		for (int i = 0; i < K; ++i)
			for (int j = 0; j < K; ++j)
				el[i][j] = 1;
		int w = 1;
		while (cnt) {
			el[x][y]++;
			int nx = (x * X + y * w * Y + O) % K;
			int ny = (x * w * X + y * Y + O) % K;

            x = nx;
			y = ny;

			++w;
			--cnt;
		}
	}
	Matrice operator * (const Matrice &oth) const {
		Matrice rez;
		for (int i = 0; i < K; ++i)
			for (int j = 0; j < K; ++j) {
				int x = 0;
				for (int k = 0; k < K; ++k)
					x += el[i][k] * oth.el[k][j];
				rez.el[i][j] = (x % MOD);
			}
		return rez;
	}
	void show() {
		for (int i = 0; i < K; ++i, cerr << '\n')
			for (int j = 0; j < K; ++j)
				cerr << el[i][j] << '\t';
		cerr << "\n\n";
	}
} roads[kMaxN], aint[4 * kMaxN], Matrice_empty;

void aint_make(int nod, int st, int dr) {
 	if (st == dr) {
		aint[nod] = roads[st];
		return ;
	}
	int m = (st + dr) / 2;
	aint_make(2 * nod, st, m);
	aint_make(2 * nod + 1, m + 1, dr);

	aint[nod] = aint[2 * nod] * aint[2 * nod + 1];
}

void aint_remake(int nod, int st, int dr, int c) {
	if (st == dr) {
		aint[nod] = roads[st];
		return ;
	}
	int m = (st + dr) / 2;
	if (c <= m)
		aint_remake(2 * nod, st, m, c);
	else
		aint_remake(2 * nod + 1, m + 1, dr, c);

	aint[nod] = aint[2 * nod] * aint[2 * nod + 1];
}

Matrice aint_query(int nod, int st, int dr, int c1, int c2) {
	if (dr < c1 or c2 < st) {
		return Matrice_empty;
	}
	if (c1 <= st and dr <= c2) {
		return aint[nod];
	}
	int m = (st + dr) / 2;
	return
		aint_query(2 * nod, st, m, c1, c2) *
		aint_query(2 * nod + 1, m + 1, dr, c1, c2);
}

int main() {
	in >> n >> K;
	in >> X >> Y;
	for (int i = 1; i <= n; ++i) {
		in >> cnt >> j >> k;
		roads[i] = Matrice(cnt, j, k, 0);
	}

	aint_make(1, 1, n);
	char op;
	while (in >> op) {
		if (op == 'U') {
			in >> i >> cnt >> j >> k;
			i++;
			roads[i] = Matrice(cnt, j, k, 1);
			aint_remake(1, 1, n, i);
		} else {
			int x, y;
	   		in >> i >> x >> j >> y;
			++i;
			out << aint_query(1, 1, n, i, j).el[x][y] << '\n';
		} 
	}
	return 0;
}
