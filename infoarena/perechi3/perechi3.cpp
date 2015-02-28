//Problem perechi3 from Infoarena
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

ifstream in("perechi3.in");
ofstream out("perechi3.out");

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		in >> n;
		int64 rez = 0;
		int itr = 1;
		for (itr = 1; itr * itr <= n; ++itr) {
			rez += max(0, n / itr - itr + 1);
		}
		--itr;
		rez *= 2;
		rez -= itr;
		out << rez << '\n';
	}
	return 0;
}
