//Problem pba from Infoarena
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

const int inf = 0x3f3f3f3f, Mod = 1000000007;

ifstream in("pba.in");
ofstream out("pba.out");

int mx[3];

void check(int a) {
	if (a > mx[0]) {
		mx[2] = mx[1];
		mx[1] = mx[0];
		mx[0] = a;
	} else {
		if (a > mx[1]) {
			mx[2] = mx[1];
			mx[1] = a;
		} else {
			if (a > mx[2]) {
				mx[2] = a;
			}
		}
	}
}

int main() {
	int n;
    in >> n;
	for (int i = 1; i <= n; ++i) {
		int a;
		in >> a;
		check(a);
	}
	out << (((1LL * mx[0] * mx[1]) % Mod) * mx[2]) % Mod;
	return 0;
}
