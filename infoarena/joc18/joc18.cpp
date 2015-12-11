//Problem joc18 from Infoarena
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

const int kMaxVal = 1000005;

ifstream in("joc18.in");
ofstream out("joc18.out");

int dv[kMaxVal];

int d(int x) {
	if (x == 1)
		return 0;
	return d(x / dv[x]) + 1;
}

int main() {
	dv[1] = 1;
    for (int i = 2; i < kMaxVal; ++i)
		if (dv[i] == 0) {
			dv[i] = i;
 			for (int64 j = 1LL * i * i; j < kMaxVal; j += i)
				dv[j] = i;
		}

	int t;

	in >> t;
 	while (t--) {
		int mx = -1, mn = kMaxVal, n;
		in >> n;
		for (int i = 1; i <= n; ++i) {
			int x;
			in >> x;
			int p = d(x);
			if (mx < p)
				mx = p;
			if (mn > p)
				mn = p;
		}

		if (mn == mx)
			out << "Aurel\n";
		else
			out << "Bianca\n";
	}
	return 0;
}
