#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("lgput.in");
ofstream out("lgput.out");

const int Mod = 1999999973;

int64 pow(int a, int p, int Mod) {
	int64 rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % Mod;
		a = (1LL * a * a) % Mod;
		p /= 2;
	}
	return rez;
}

int main() {
	int64 n, p;
	in >> n >> p;
	out << pow(n, p, Mod);
    return 0;
}
