//Problem minesweeper2 from Infoarena
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

const int inf = 0x3f3f3f3f, Mod = 666013, kMaxN = 300005;

ifstream in("minesweeper2.in");
ofstream out("minesweeper2.out");

int nr_b[8] = {0, 1, 1, 2, 1, 2, 2, 3};
int rez[8][kMaxN];

int el[kMaxN];

void mod(int &a) {
	while (a >= Mod)
		a -= Mod;
}

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
 	for (int i = 0; i < 8; ++i)
		rez[i][1] = 1;
	for (int i = 1; i <= n; ++i) {
		if (i == 1)
			rez[4][1] = rez[5][1] = rez[6][1] = rez[7][1] = 0;
		if (i == n)
			rez[1][n] = rez[3][n] = rez[5][n] = rez[7][n] = 0;
			
			for (int t = 0; t < 8; ++t) {
				if (nr_b[t] != el[i] and el[i] != -1)
					rez[t][i] = 0;
				rez[(t & 3) * 2][i + 1] += rez[t][i];
				rez[(t & 3) * 2 + 1][i + 1] += rez[t][i];
				mod(rez[(t & 3) * 2 + 1][i + 1]);
			}
	}
	int R = 0;
	for (int i = 0; i < 8; ++i) {
		R += rez[i][n];
		mod(R);
	}
	out << R << '\n';
	return 0;
}
