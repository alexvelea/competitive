//Problem b from googleCodeJam2015Round1B
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1000001;

ifstream fin("data.in");
ofstream fout("data.out");

int best[kMaxN], bfs[kMaxN];

int mirror(int a) {
	int rez = 0;
	while (a) {
		rez *= 10;
		rez += a % 10;
		a /= 10;
	}
	return rez;
}

int main() {
	ios::sync_with_stdio(false);
 	int t; fin >> t;
	best[1] = 1;
	int st = 0, dr = 1;
 	bfs[++st] = 1;
	while (st <= dr) {
		int nod = bfs[st++];
		if (nod + 1 < kMaxN and best[nod + 1] == 0) {
			bfs[++dr] = nod + 1;
			best[nod + 1] = best[nod] + 1;
		}
		if (best[mirror(nod)] == 0) {
			bfs[++dr] = mirror(nod);
			best[mirror(nod)] = best[nod] + 1;
		}
	}
	for (int i = 1; i <= t; ++i) {
		int x; fin >> x;
		fout << "Case #" << i << ": " << best[x] << '\n';
	}
	return 0;
}
