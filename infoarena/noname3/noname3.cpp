//Problem noname3 from Infoarena
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

ifstream in("noname3.in");
ofstream out("noname3.out");

int main() {
	int n, s;
	in >> n >> s;
	int64 S = 1LL * n * (n + 1) / 2;
	if (S > s) {
		out << "-1\n";
	} else {
		int init = (s - S) / n;
		s -= init * n;
		s -= S;
		for (int i = 1; i <= n - s; ++i)
			out << i + init << ' ';
		for (int i = n - s + 1; i <= n; ++i)
			out << i + init + 1 << ' ';
	}
	return 0;
}
