//Problem semipal from Infoarena
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

const int inf = 0x3f3f3f3f;

ifstream in("semipal.in");
ofstream out("semipal.out");

int rez[66];

int main() {
	int t;
    in >> t;
	while (t--) {
		int n;
		int64 k;
		in >> n >> k;
		k--;
		for (int i = 1; i <= n; ++i) {
			rez[i] = 0;
		}
		for (int i = n - 1; i > 0; --i) {
			if (k & 1)
				rez[i] = 1;
			k /= 2;
		}
		rez[n] = rez[1];
		for (int i = 1; i <= n; ++i)
			out << ((rez[i] == 0) ? ('a') : ('b'));
		out << "\n";
	}
	return 0;
}
