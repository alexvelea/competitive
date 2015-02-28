//Problem xor from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxT = 20005;

ifstream in("xor.in");
ofstream out("xor.out");

int Mod;

int solve(int x, int y) {
	int rez = 0;
	for (int l = 0; (1 << l) <= max(x, y); ++l) {
		int a = (x + 1) / (1 << l);
		int b = (y + 1) / (1 << l);
		int64 r = 0;
		r += ((1LL * a * b / 2) << (2 * l))
			+ 1LL * ((y + 1) & ((1 << l) - 1)) * (((a + (b % 2)) / 2) << l)
			+ 1LL * ((x + 1) & ((1 << l) - 1)) * (((b + (a % 2)) / 2) << l)
			+ 1LL * ((a + b) & 1) * ((x + 1) & ((1 << l) - 1)) * ((y + 1) & ((1 << l) - 1));

		r = (1LL * (r % Mod) * (1 << l)) % Mod;
		rez += r;
	}
	rez %= Mod;
	return rez;
}

int X[kMaxT], Y[kMaxT], C1[kMaxT], C2[kMaxT];

int main() {
	int t;
 	in >> t >> Mod;
	for (int i = 1; i <= t; ++i)
		in >> C1[i] >> C2[i] >> X[i] >> Y[i];
	for (int i = 1; i <= t; ++i) {
		int c1, c2, x, y;
		c1 = C1[i]; c2 = C2[i]; x = X[i]; y = Y[i];
		c1--;
		c2--;
		int rez = 0;
		rez = solve(x, y);
		rez += solve(c1, c2);
		rez %= Mod;
		rez -= solve(c1, y);
		rez -= solve(x, c2);
		while (rez < 0)
			rez += Mod;
		out << rez << '\n';
	}
	return 0;
}
