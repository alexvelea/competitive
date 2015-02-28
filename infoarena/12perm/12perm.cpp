//Problem 12perm from Infoarena
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

ifstream in("12perm.in");
ofstream out("12perm.out");

int rez[10000];

int main() {
	int n;
	in >> n;
 	rez[1] = 1;
	rez[2] = 1;
	rez[3] = 2;
	for (int i = 4; i <= n; ++i) {
		rez[i] = rez[i - 1] + rez[i - 3] + 1;
	}
	cerr << rez[n] * 2<< '\n';
 	rez[n] *= 2;
	rez[n] += (n - 2) * 2;
	out << rez[n] << '\n';

	return 0;
}
