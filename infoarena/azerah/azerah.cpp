//Problem azerah from Infoarena
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

ifstream in("azerah.in");
ofstream out("azerah.out");

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		in >> n;
		bool impar = false;
		int rez = 1;
		for (int i = 1; i <= n; ++i) {
			int el;
			in >> el;
			if (el & 1) {
				impar = true;
			}
		}
		for (int i = 1; i < n; ++i) {
			rez *= 2;
			if (rez >= Mod) {
				rez -= Mod;
			}
		}
		if (not impar) {
			rez = (2 * rez) % Mod;
		}
		rez--;
		if (rez == -1) {
			rez += Mod;
		}

		out << rez << '\n';
	}
	return 0;
}
