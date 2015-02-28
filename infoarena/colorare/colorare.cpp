//Problem colorare from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 15;

ifstream in("colorare.in");
ofstream out("colorare.out");

bool ok[1 << kMaxN], edge[kMaxN][kMaxN];
int best[1 << kMaxN];
int64 rez[1 << kMaxN];

bool correct(int stare) {
	bool ok = true;
	for (int i = 0; i < 15; ++i)
		if (stare & (1 << i))
		for (int j = 0; j < 15; ++j)
			if (stare & (1 << j) and edge[i][j])
				ok = false;
	return ok;
}

void bt(int it, int dr, int st, int base) {
	if (ok[st] == false)
		return ;
	if (it == dr) {
		if (best[st | base] > best[base] + 1) {
			best[st | base] = best[base] + 1;
			rez[st | base] = 0;
		}
		if (best[st | base] == best[base] + 1)
			rez[st | base] += rez[base];
		return ;
	}
	bt(it + 1, dr, st, base);
	if (not (base & (1 << it)))
		bt(it + 1, dr, st | (1 << it), base);
}

int main() {
	int n, m;
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
		a--;
		b--;
		edge[a][b] = edge[b][a] = true;
	}

	for (int i = 1; i < (1 << n); ++i)
		best[i] = inf;
	rez[0] = 1;

	for (int i = 0; i < (1 << n); ++i)
		ok[i] = correct(i);
// 	for (int i = 0; i < (1 << n); ++i)
//		cerr << i << '\t' << ok[i] << '\n';   	
	
	for (int i = 0; i < (1 << n); ++i) {
		bt(0, n, 0, i);
	}
	out << best[(1 << n) - 1] << ' ' << rez[(1 << n) - 1];
	return 0;
}
