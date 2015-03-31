//Problem tictac from Infoarena
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

ifstream in("tictac.in");
ofstream out("tictac.out");

int main() {
	int t; in >> t;
	while (t--) {
		double a, b; in >> a >> b;
		b = b * 60.0 / 360.0;
		a = a * 12.0 * 60.0 / 360.0;
		while (a > 60.0) {
			a -= 60.0;
		}
//		cerr << a << '\t' << b << '\n';
		if (fabs(a - b) < 0.01 or fabs(60 - fabs(a - b)) < 0.01) {
			out << "1\n";
		} else {
			out << "0\n";
		}
	}
	return 0;
}
