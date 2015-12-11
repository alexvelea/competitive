//Problem B from Codeforces Round facebookHackerCup2015Qualification
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

ifstream in("input.txt");
ofstream out("output.txt");

int A[22], B[22], C[22];

int main() {
    int t;
	in >> t;
	for (int T = 1; T <= t; ++T) {
		bool ok = false;
		int a, b, c, n;
		in >> a >> b >> c;
		in >> n;
		for (int i = 0; i < n; ++i) {
			in >> A[i] >> B[i] >> C[i];
		}
		for (int p = 0; p < (1 << n); ++p) {
			int _a = a, _b = b, _c = c;
			for (int i = 0; i < n; ++i) {
				if (p & (1 << i)) {
					_a -= A[i];
					_b -= B[i];
					_c -= C[i];
				}
			}
			if (_a == 0 and _b == 0 and _c == 0) 
				ok = true;
		}
		if (ok) 
			out << "Case #" << T << ": yes\n";
		else
			out << "Case #" << T << ": no\n";
	}
	return 0;
}
