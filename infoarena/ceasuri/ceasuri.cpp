//Problem ceasuri from Infoarena
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
const double eps = 0.00001;

ifstream fin("ceasuri.in");
ofstream fout("ceasuri.out");

int main() {
	int t; fin >> t;
	while (t--) {
		int H, M; fin >> H >> M;
		H /= 2;
		int rez = 0;
		for (int i = 0; i + 1 < H; ++i) {
			double where = 1.0 * i / (H - 1);
			double min = 1.0 * where * H - floor(1.0 * where * H);
			double sec = 1.0 * min * M - floor(1.0 * min * M);
			if (abs(sec - min) < eps) 
				rez++;
		}
		rez *= 2;
		fout << rez << '\n';
	}
	return 0;
}
