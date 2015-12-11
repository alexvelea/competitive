//Problem aurel from Infoarena
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

const int inf = 0x3f3f3f3f, Mod = 666013;

ifstream fin("aurel.in");
ofstream fout("aurel.out");

void mod(int &a) {
	if (a >= Mod) {
		a -= Mod;
	}
}

int rez[105][105];

int n[10], m[10], r[10];

int main() {


	int t; fin >> t;

	for (int i = 1; i <= t; ++i) {
		fin >> n[i] >> m[i];
		r[i] = -1;
	}

		rez[1][1] = 1;
 		for (int l = 0; l <= 100000; ++l) {
 			for (int i = 1; i <= 100; ++i) {
 				for (int j = 1; j <= t; ++j) {
					if (n[j] == i and m[j] == l) {
						r[j] = rez[i][l % 105];
					}
				}
 				
				mod(rez[i][l % 105]);
				rez[i][(l + i) % 105] += rez[i][l % 105];
				rez[i + 1][(l + i + 1) % 105] += rez[i][l % 105];
				rez[i][l % 105] = 0;
			}
		}

	for (int i = 1; i <= t; ++i) {
		assert(r[i] != -1);
		fout << r[i] << '\n';
	}
	return 0;
}
