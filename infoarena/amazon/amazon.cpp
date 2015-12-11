//Problem amazon from Infoarena
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

ifstream in("amazon.in");
ofstream out("amazon.out");

int main() {
	int nr_c, nr_x, nr_t;
	int rez[100];
	char r[26 * 2];
	in >> nr_c >> nr_x >> nr_t;
	for (int t = 1; t <= nr_c * nr_x; ++t)
		in >> rez[t];
	for (int i = 0; i < 26; ++i) {
		r[i] = char('a' + i);
		r[26 + i] = char('A' + i);
	}
	for (int i = 1; i <= nr_x; ++i) {
		for (int j = 1; j <= nr_c; ++j) {
			out << rez[(i - 1) * nr_c + j] << " = ";
			for (int k = 1; k <= nr_t; ++k) {
				out << r[(k - 1) * (nr_c + nr_x) - 1 + j] << "*" << r[(k - 1) * (nr_c + nr_x) + nr_c + i - 1] << " + ";
			}
			out << ",\n";
		}
	}
	return 0;
}
