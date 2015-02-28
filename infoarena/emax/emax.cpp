//Problem emax from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005, Mod = 666013;

ifstream in("emax.in");
ofstream out("emax.out");

double best[kMaxN];
int rez[kMaxN], val[kMaxN];

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> val[i];
		if (val[i] < 0)
			val[i] = -val[i];
		if (val[i] == 0) {
			--n;
			--i;
		}
	}

	best[0] = 0;
    rez[0] = 1;

	for (int i = 1; i <= n; ++i) {
		int prod = 0;
		for (int j = i; j >= 1 and j + 2 >= i; --j) {
			prod += val[j];
			
			if (log(prod) + best[j - 1] > best[i]) {
				best[i] = log(prod) + best[j - 1];
				rez[i] = (1LL * rez[j - 1] * prod) % Mod;
			}
		}
	}
	out << rez[n] << '\n';
	return 0;
}
