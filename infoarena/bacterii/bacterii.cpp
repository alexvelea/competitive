#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("bacterii.in");
ofstream out("bacterii.out");

int pow(int64 a, int64 p, int Mod) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % Mod;
		a = (1LL * a * a) % Mod;
		p /= 2;
	}
	return rez;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		int64 k;
		int Mod;
		in >> n >> k >> Mod;

        assert(Mod != 3);

		if (n == 1) {
			out << 1 << '\n';
			continue;
		}
    	
        if (Mod == 3) {
			k %= 6;
			if (k == 0)
				k = 6;
			n %= 3;
 			while (k--) {
            	n = (n * n - 2 * n + 2 + 12) % 3;
			}
			out << n << '\n';
			continue;
		}

		k = pow(2, k, Mod - 1);
		n = pow(n - 1, k, Mod);
		out << (n + 1) % Mod<< '\n';
	}
    return 0;
}
