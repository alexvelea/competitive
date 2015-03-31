//Problem mafia from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("mafia.in");
ofstream out("mafia.out");

double fact(int64 a) {
	return a * log(a) - a;
}

int main() {
	int t; in >> t;
	while (t--) {
		int64 m, sum = 0, total = 0;
		int n, x; in >> n >> m >> x; x--;
		for (int i = 0; i < n; ++i) {
            int el; in >> el;
			sum += el;
			total += el;
			if (i == x) {
				sum -= el;
			}
		}
        if (m > sum) {
			out << "1.0000000000\n";
			continue;
		}

		double prb = 1.0;
		if (1) {
			int64 drS = min(total - m, sum);
			int64 stT = max(sum + 1, total - m + 1);
			for (; stT <= total and prb >= 0.0000000001; --drS, ++stT) {
				prb *= drS;
				prb /= stT;
			}
		} else {
			// frumoasa rezolvare, dar nu prea
			prb = fact(sum) + fact(total - m) - fact(sum - m) - fact(total);
			prb = pow(M_E, prb);
		}

		out << fixed << setprecision(9) << 1.0 - prb << '\n';
	}
	return 0;
}
