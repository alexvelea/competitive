#include <fstream>
#include <iostream>
using namespace std;

ifstream in("concert2.in");
ofstream out("concert2.out");

const int kMaxN = 2505, kMaxK = 305;

int up[kMaxN][kMaxK], daws[kMaxN][kMaxK];
int el[kMaxN];

int main() {
	int n, a, b;
	in >> n >> a >> b;
	for (int i = 1; i <= n; ++i)
		in >> el[i];
	up[1][1] = 1;
	daws[1][1] = 1;
	for (int dr = 2; dr <= n; ++dr) {
		for (int st = 1; st < dr; ++st) {
	    	for (int k = 2; k <= a; ++k)	
				if (el[st] < el[dr])
					up[dr][k] = max(up[dr][k], 1 + up[st][k - 1]);
			for (int k = 1; k <= b; ++k)
				if (el[st] > el[dr])
					up[dr][2] = max(up[dr][2], 1 + daws[st][k]);

			for (int k = 2; k <= b; ++k)
				if (el[st] > el[dr])
					daws[dr][k] = max(daws[dr][k], 1 + daws[st][k - 1]);
			for (int k = 1; k <= a; ++k)
				if (el[st] < el[dr])
					daws[dr][2] = max(daws[dr][2], 1 + up[st][k]);
			daws[dr][1] = up[dr][1] = 1;
		}
/*		for (int i = 1; i <= a; ++i)
			cerr << up[dr][i] << '\t';
		cerr << '\n';
		for (int i = 1; i <= b; ++i)
			cerr << daws[dr][i] << '\t';
		cerr << "\n\n";*/
	}
	int rez = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= a; ++j)
			rez = max(rez, up[i][j]);
		for (int j = 1; j <= b; ++j)
			rez = max(rez, daws[i][j]);
	}
	out << rez << '\n';
	return 0;
}
