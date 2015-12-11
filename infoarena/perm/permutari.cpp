#include <fstream>
#include <iostream>
using namespace std;

const int kMaxCif = 200, sigma = 1000000, kNrCif = 6, kMaxN = 205;

ifstream in("perm.in");
ofstream out("perm.out");

struct BigNumber {
	int nr_cif;
	int cif[kMaxCif];

	BigNumber() {
		nr_cif = 1;
		for (int i = 0; i < kMaxCif; ++i)
			cif[i] = 0;
	}

	void add(BigNumber oth, int exp) {
		// exp <= 200 -> sigma <= 10 ^ 7
		int i;
		nr_cif = max(nr_cif, oth.nr_cif);
		for (i = 0; i < nr_cif; ++i) {
			cif[i] += oth.cif[i] * exp;
			if (cif[i] >= sigma) {
				cif[i + 1] += cif[i] / sigma;
				cif[i] %= sigma;
				nr_cif = max(i + 2, nr_cif);
			}
		}
		nr_cif = i;
	}

	string show() {
		string rez = "";
		for (int i = nr_cif - 1; i >= 0; --i) {
			int c[6];
			for (int j = 0; j < 6; ++j)
				c[j] = 0;

			int x = cif[i];
			int j = kNrCif - 1;
			while (x) {
				c[j] = x % 10;
				--j;
				x /= 10;
			}
			int z = false;
			for (int j = 0; j < kNrCif; ++j) 
    			if (i == nr_cif - 1) {
					if (c[j] == 0) {
						if (z)
							rez += '0';
					} else {
						z = true;
						rez += char(c[j] + '0');
					}
				} else
					rez += char(c[j] + '0');
		}
		if (rez == "")
			rez += '0';
		return rez;
	}
} sol[kMaxN];

int main() {
	int n, k;
	in >> n >> k;
	sol[1].cif[0] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = k; j; --j) {
			if (j != k)
				sol[j + 1].add(sol[j], 1);
 			sol[j].add(sol[j], i - 2);
		}
	}
	out << sol[k].show() << '\n';
}
