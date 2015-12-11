//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("matperm2.in");
ofstream out("matperm2.out");

const int kMaxN = 1005;

int el[kMaxN][kMaxN], c[kMaxN], l[kMaxN];
int where[kMaxN * kMaxN], viz[kMaxN * kMaxN], rez[kMaxN * kMaxN];

int main() {
	int n, m, p;
	in >> n >> m >> p;
	for (int i = 1; i <= n; ++i)
		in >> l[i];
	for (int i = 1; i <= m; ++i)
		in >> c[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int I = l[i];
			int J = c[j];
			el[i][j] = (I - 1) * m + J;
		}
    

/*	for (int i = 1; i <= n; ++i, cerr << '\n')
		for (int j = 1; j <= m; ++j)
			cerr << el[i][j] << ' ';*/

	int q;
	in >> q;
 	while (q--) {
		int x, y, a, b;
		in >> x >> y >> a >> b;
		swap(el[x][y], el[a][b]);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			where[el[i][j]] = (i - 1) * m + j;
		}
	for (int i = 1; i <= n * m; ++i) {
    	int nod = i;
		if (viz[nod])
			continue;
		int l = 0;
		while (viz[nod] == false) {
			++l;
			viz[nod] = true;
			nod = where[nod];
		}
		int P = p % l;
		int nod2 = nod;
		while (P--) {
			nod2 = where[nod2];
		}
		
		do {
			rez[nod2] = nod;
			nod = where[nod];
			nod2 = where[nod2];
		} while (nod != i);

	}
	for (int i = 1; i <= n * m; ++i) {
		out << rez[i] << ' ';
		if (i % m == 0)
			out << '\n';
	}
	return 0;
}
