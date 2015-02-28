//Problem oras from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 205;

bool edge[kMaxN][kMaxN];

ifstream in("oras.in");
ofstream out("oras.out");

bool ok(int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			bool ok = false;
			if (edge[i][j] == 1)
				ok = true;
			if (i == j)
				ok = true;
			for (int l = 1; l <= n; ++l)
				if (edge[i][l] and edge[l][j])
					ok = true;
			if (ok == false)
				return false;
		}
	}
	return true;
}


void init(int b) {
	if (b == 1) {
		edge[1][2] = edge[2][3] = edge[3][1] = true;
	} else {
		int n = 6;
		for (int i = 0; i < (1 << (n) * (n - 1) / 2); ++i) {
			int st = i;
			for (int a = 1; a <= n; ++a)
				for (int b = 1; b < a; ++b) {
					edge[a][b] = st % 2;
					st /= 2;
					edge[b][a] = 1 - edge[a][b];
				}
//			for (int a = 1; a <= n; ++a, cerr << '\n')
//				for (int b = 1; b <= n; ++b)
//					cerr << edge[a][b];
//			cerr << "\n\n";
			if (ok(n)) {
//				cerr << "PENIS!";
		   		return ;
			}
		}
	}
}

void add(int n) {
	for (int i = 1; i <= n; ++i) {
		edge[i][n + 1] = 1;
		edge[n + 2]	[i] = 1;
	}
	edge[n + 1][n + 2] = 1;
}

int main() {
	int n;
	in >> n;
	
	if (n == 4) {
		out << "-1\n";
		return 0;
	}
	
	init(n % 2);
	int st[2] = {6, 3};
	for (int i = st[n % 2]; i < n; i += 2) {
		add(i);
	}
	for (int i = 1; i <= n; ++i, out << '\n')
		for (int j = 1; j <= n; ++j)
			out << edge[i][j];
	return 0;
}
