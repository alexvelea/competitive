//Problem twosets from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, nrMod = 2, Mod[2] = {1000000021, 1000000009};

int inv[11][2];

ifstream in("twosets.in");
ofstream out("twosets.out");

unordered_map<int, int> ap;

int solve(int base, int sign) {
	string txt;
	in >> txt;
	string chr;
	chr.reserve(txt.size() / 2);

    int n = 0;
	int rez[nrMod] = {0, 0};

	for (auto itr : txt) {
		if (itr == 'i') {
			continue;
		}

		if (itr == 'd') {
 		    if (chr.size()) {
				char c = chr[chr.size() - 1];
				
				for (int i = 0; i < nrMod; ++i) {
					rez[i] -= c - '0';
					if (rez[i] < 0)
						rez[i] += Mod[i];
					rez[i] = (1LL * rez[i] * inv[base][i]) % Mod[i];
				}

				chr.pop_back();
			}
			continue;
		}

		if (itr == 't') {
			++n;
//			cerr << rez[0] << '\t' << base << '\n';
//			string a = to_string(rez[0]) + '#' + to_string(rez[1]);
//			cerr << ap[a] << '\t' << a << '\n';
			int a = rez[0];
			ap[a] += sign;
			if (ap[a] < 0)
				n = inf;
			continue;
		}
 			

        char c = itr;
		chr += c;
		for (int i = 0; i < nrMod; ++i) {
			rez[i] = (1LL * base * rez[i] + c - '0') % Mod[i];
		}
	}
	return n;
}

int pow(int a, int p, int Mod) {
	int rez = 1;
	while (p) {
		if (p & 1) {
			rez = (1LL * rez * a) % Mod;
		}
		a = (1LL * a * a) % Mod;
		p /= 2;
	}
	return rez;
}

int main() {
	inv[2][0] = pow(2, Mod[0] - 2, Mod[0]);
	inv[2][1] = pow(2, Mod[1] - 2, Mod[1]);
	inv[10][0] = pow(10, Mod[0] - 2, Mod[0]);
	inv[10][1] = pow(10, Mod[1] - 2, Mod[1]);

	int t; in >> t;
	while (t--) {
		ap.clear();
 		int n = solve(2, +1);
		int m = solve(10, -1);
//		cerr << n << '\t' << m << '\n';
		if (n == m)
			out << "1\n";
		else
			out << "0\n";
	}
	return 0;
}
