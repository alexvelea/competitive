#include <fstream>
#include <iostream>
using namespace std;

const int Mod = 666013, kMaxL = 90;

#define int64 long long
ifstream in("ikebana.in");
ofstream out("ikebana.out");

int codif(int i, int p, int s) {
	int rez = 0;
	if (i == -1)
		rez = 0;
	if (i == 0)
 		rez = 2 * 21;
	if (s == 0)
		rez += p;
	else
		rez += p + 21;
	return rez;
}

struct Matrice {
	int el[kMaxL][kMaxL];
 	Matrice() {
		for (int i = 0; i < kMaxL; ++i)
			for (int j = 0; j < kMaxL; ++j)
				el[i][j] = 0;
		for (int i = 0; i < kMaxL; ++i)
			el[i][i] = 1;
	}
	void Inm(Matrice rhs) {
		Matrice rez;
		for (int i = 0; i < kMaxL; ++i)
			for (int j = 0; j < kMaxL; ++j) {
				int64 r = 0;
				for (int l = 0; l < kMaxL; ++l)
					r += 1LL * el[i][l] * rhs.el[l][j];
				rez.el[i][j] = r % Mod;
			}
		for (int i = 0; i < kMaxL; ++i)
			for (int j = 0; j < kMaxL; ++j)
				el[i][j] = rez.el[i][j];
	}
} a, b;

Matrice pow(Matrice a, int p) {
	Matrice rez;
	while (p) {
		if (p % 2)
			rez.Inm(a);
		a.Inm(a);
		p /= 2;
	}
	return rez;
}

int main() {
	int n, p, t;
	in >> n >> p >> t;
	
	for (int i = 0; i < kMaxL; ++i)
		a.el[i][i] = b.el[i][i] = 0;

		int x, y;
		for (int i = 0; i <= p; ++i)
			for (int z = 0; z < 2; ++z) {
				int x = codif(-1, i, z);
				int y = codif(0, i, z);
				a.el[x][y] += 1;
			}

        x = codif(0,0,0);
		y = codif(0,p,0);
		a.el[x][y] += 1;

		y = codif(0,p,1);
		a.el[x][y] += 1;

		for (int j = 1; j <= p; ++j) {
			int x, y;
			x = codif(0, j, 0);
			y = codif(0, j - 1, 0);
			a.el[x][y] += t - 4;
			y = codif(0, j - 1, 1);
			a.el[x][y] += t - 4;

 			x = codif(0, j, 1);
			y = codif(0, j - 1, 0);
			a.el[x][y] += 2;
			y = codif(0, j - 1, 1);
			a.el[x][y] += 2;

			if (j > 1) {
		    	y = codif(-1, j - 2, 1);
				a.el[x][y] += 1;
			}
		}
 		
		x = codif(0, p, 0);
		y = codif(0, p, 0);
		a.el[x][y] += t - 4;

		y = codif(0, p, 1);
		a.el[x][y] += t - 4;

 		x = codif(0, p, 1);
		y = codif(0, p, 1);
		a.el[x][y] += 2;

		y = codif(0, p, 0);
		a.el[x][y] += 2;

 		y = codif(-1, p, 1);
		a.el[x][y] += 1;

		y = codif(-1, p - 1, 1);
		a.el[x][y] += 1;

	b.el[codif(0,0,0)][0] = 1;
	b.el[codif(0,p,1)][0] = 2;
	b.el[codif(0,p,0)][0] = t - 4;

	a = pow(a, n - 1);
	a.Inm(b);

	int64 rez = 0;
	for (int i = 0; i < kMaxL; ++i)
		for (int j = 0; j < kMaxL; ++j) {
        	if (i >= codif(0,0,0))
				rez += a.el[i][j];
			rez %= Mod;
		}
	out << rez << '\n';
//	cerr << rez << '\n';
	return 0;
}
