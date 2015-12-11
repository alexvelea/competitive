//Problem tango from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005, Mod = 999983;

ifstream in("tango.in");
ofstream out("tango.out");

void mod(int &a) {
	if (a >= Mod) {
		a -= Mod;
	}
}

int logPow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1) {
			rez = (1LL * rez * a) % Mod;
		}
		p /= 2;
		a = (1LL * a * a) % Mod;
	}
	return rez;
}

int a[kMaxN], rez[20];

int main() {
	int n, k;
	in >> n >> k;
	for (int i = 1; i <= n; ++i) {
		in >> a[i];
	}
	rez[0] = 1;
	for (int t = 0; t < 8; ++t) {
		for (int i = 1; i <= n; ++i) {
			rez[t + a[i]] += rez[t];
			mod(rez[t + a[i]]);
		}
	}
	k /= 8;
	out << logPow(rez[8], k);
	return 0;
}
