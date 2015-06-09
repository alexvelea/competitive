//Problem nogame from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 1005, kMaxK = 17;

ifstream fin("nogame.in");
ofstream fout("nogame.out");

struct Sir {
	int el[kMaxN], n;
 	Sir() {
		for (int i = 0; i < kMaxN; ++i) {
			el[i] = 0;
		}
	}
	Sir(int _n) {
		n = _n;
 		for (int i = 0; i < kMaxN; ++i) {
			el[i] = 0;
		}   	
	}

	bool operator < (const Sir &rhs) const {
		for (int i = 1; i <= n; ++i) {
			if (el[i] != rhs.el[i]) {
				return el[i] < rhs.el[i];
			}
		}
		return 0;
	}

	Sir apply(int ind) {
		bool M[2][2];
		M[0][0] = ((ind & (1 << 3)) != 0);
		M[0][1] = ((ind & (1 << 2)) != 0);
		M[1][0] = ((ind & (1 << 1)) != 0);
		M[1][1] = ((ind & (1 << 0)) != 0);

		Sir rez(n);
		rez.el[1] = el[1];
/*		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				cerr << M[i][j];
			}
		}
    	cerr << "<-\t";*/
		for (int i = 2; i <= n; ++i) {
			int nr = 0;
			for (int j = 0; j < 30/* and (rez.el[i - 1] >= (1 << j) or el[i] >= (1 << j))*/; ++j) {
				if ((rez.el[i - 1] & (1 << j)) or (el[i] & (1 << j))) {
					nr = j;
				}
			}
 			
			for (int j = 0; j <= nr; ++j) {
				int a = M[((rez.el[i - 1] & (1 << j)) != 0)][((el[i] & (1 << j)) != 0)]; //cerr << a;
				rez.el[i] |= a << j;
			}
//			cerr << '\t';
		}
//		cerr << '\n';
		return rez;
	}

	bool operator == (const Sir &rhs) const {
		if (n != rhs.n) {
			return false;
		}

		for (int i = 1; i <= n; ++i) {
			if (el[i] != rhs.el[i]) {
				return false;
			}
		}
		return true;
	}
} start[kMaxK], rez, finish[kMaxK];

int main() {
	int t; fin >> t;
	while (t--) {
		int n; fin >> n;
		for (int i = 1; i <= 16; ++i) {
			start[i].n = n;
			for (int j = 1; j <= n; ++j) {
				fin >> start[i].el[j];
			}
		}
	
		sort(start + 1, start + 16 + 1);

		int f = -1;
		for (int i = 1; i <= 16; ++i) {
			finish[6] = start[i];
			for (int j = 1; j <= 16; ++j) {
				if (j == 6) 
					continue;
				finish[j] = finish[6].apply(j - 1);		
			}
			sort(finish + 1, finish + 16 + 1);
/* 			for (int i = 1; i <= 16; ++i) {
				for (int j = 1; j <= n; ++j) {
					fout << finish[i].el[j] << ' ';
				}
				fout << '\t';
 				for (int j = 1; j <= n; ++j) {
					fout << start[i].el[j] << ' ';
				}
				fout << '\n';
			}*/

			bool ok = true;
			for (int j = 1; ok and j <= 16; ++j) {
				if (not (finish[j] == start[j])) {
					ok = false;
				}
			}
			
			if (ok) {
				if (f == -1) {
					f = i;
				} else {
					if (start[i] < start[f]) {
						f = i;
					}
				}
			}
		}

		if (f == -1) {
			fout << "-1\n";
		} else {
			for (int i = 1; i <= n; ++i) {
				fout << start[f].el[i] << ' ';
			}
			fout << '\n';
		}
	}
	return 0;
}
