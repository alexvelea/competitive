#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

ifstream in("dlog.in");
ofstream out("dlog.out");

unordered_map <int, int> exponent;

int pow (int x, int p, int MOD) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * x) % MOD;
		x = (1LL * x * x) % MOD;
		p >>= 1;
	}
	return rez;
}

int main() {
	int T;
	in >> T;
	while (T--) {
		int P, G, Y;
		in >> P >> G >> Y;
		int x = 1;
		if (Y == 1) {
			out << "0\n";
			continue;
		}
		for (int i = 1; i <= 1000 && i < P; ++i) {
			x = (1LL * x * G) % P;
			exponent[x] = i;
		}
		int b = pow(x, P-2, P);
		int ex = 1;
		for (int i = 0; ; ++i, ex = (1LL * ex * b) % P) {
			int e = (1LL * ex * Y) % P;
			if (exponent[e] != 0) {
				out << 1000 * i + exponent[e] << "\n";
				break;
			}
		}
		exponent.clear();
	}
	return 0;
}


