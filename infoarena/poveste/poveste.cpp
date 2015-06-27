//Problem poveste from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 1005;

ifstream in("poveste.in");
ofstream out("poveste.out");

char el[kMaxN][kMaxN];

int ord[kMaxN], toNext[kMaxN], newOrd[kMaxN], newToNext[kMaxN];
int Min[kMaxN], Max[kMaxN];

int deq[kMaxN];

void getMax(int &a, int b) {
	if (a < b) {
		a = b;
	}
}

void getMin(int &a, int b) {
	if (a > b) {
		a = b;
	}
}


int main() {
	int t; in >> t;
	while (t--) {
		int n, m; in >> n >> m;
		int mx = 0;
		for (int i = 1; i <= n; ++i) {
 			for (int j = 1; j <= m; ++j) {
				in >> el[i][j];
			}
			el[i][0] = '0';
		}
		
		
		for (int j = 1; j <= m; ++j) {
			ord[j] = j;
			toNext[j] = 0;
		}

		for (int i = n; i; --i) {
//			cerr << mx << '\n';
			int ind = 0;
 			// 0
			int mn = -1;
			for (int j = 1; j <= m; ++j) {
				if (el[i][ord[j]] == '0') {
					++ind;
					newOrd[ind] = ord[j];
					newToNext[ind - 1] = mn + 1;
					mn = inf;
				}
				getMin(mn, toNext[j]);
			}
			mn = -1;
 			for (int j = 1; j <= m; ++j) {
				if (el[i][ord[j]] == '1') {
					++ind;
					newOrd[ind] = ord[j];
					newToNext[ind - 1] = mn + 1;
					mn = inf;
				}
				getMin(mn, toNext[j]);
			}
			
			for (int j = 1; j <= m; ++j) {
				ord[j] = newOrd[j];
				toNext[j] = newToNext[j];
			}

/*			for (int j = 1; j <= m; ++j)
				cerr << el[i][j] << '\t';
			cerr << '\n';
			for (int j = 1; j <= m; ++j) {
				cerr << ord[j] << '\t';
			}
			cerr << '\n';
 			for (int j = 1; j <= m; ++j) {
				cerr << toNext[j] << '\t';
			}   		
			cerr << "\n\n";*/
			for (int j = 1; j < m; ++j) {
				Min[j] = min(ord[j], ord[j + 1]);
				Max[j] = max(ord[j], ord[j + 1]);
			}

			int dr = 0;
			for (int j = 1; j < m; ++j) {
				int mx = -inf;
				int mn = +inf;
				while (dr and toNext[j] < toNext[deq[dr]]) {
					int poz = deq[dr];
					getMax(Max[poz], mx);
					getMin(Min[poz], mn);
					mx = Max[poz];
					mn = Min[poz];
					--dr;
				}

				if (dr) {
 					int poz = deq[dr];
					getMax(Max[poz], mx);
					getMin(Min[poz], mn);
				}

				deq[++dr] = j;
			}

			if (1) {
 				int mx = -inf;
				int mn = +inf;
				while (dr) {
					int poz = deq[dr];
					getMax(Max[poz], mx);
					getMin(Min[poz], mn);
					mx = Max[poz];
					mn = Min[poz];
					--dr;
				}   			
			}

			for (int j = m - 1; j; --j) {
				int mx = -inf;
				int mn = +inf;
				while (dr and toNext[j] < toNext[deq[dr]]) {
					int poz = deq[dr];
					getMax(Max[poz], mx);
					getMin(Min[poz], mn);
					mx = Max[poz];
					mn = Min[poz];
					--dr;
				}

				if (dr) {
 					int poz = deq[dr];
					getMax(Max[poz], mx);
					getMin(Min[poz], mn);
				}

				deq[++dr] = j;
			}

			if (1) {
 				int mx = -inf;
				int mn = +inf;
				while (dr) {
					int poz = deq[dr];
					getMax(Max[poz], mx);
					getMin(Min[poz], mn);
					mx = Max[poz];
					mn = Min[poz];
					--dr;
				}   			
			}

			for (int j = 1; j < m; ++j) {
				int c = (Max[j] - Min[j] + 1) * toNext[j];
				if (c > mx)
					mx = c;
			}
		}
		out << mx << '\n';
	}
	return 0;
}
