///Bunicule Bunicule
///Spunemi o poveste
//Problem sets from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1005;

ifstream fin("sets.in");
ofstream fout("sets.out");

double now[kMaxN], last[kMaxN];
int el[kMaxN];

int main() {
 	int t; fin >> t;
	while (t--) {
		int n, v; fin >> n >> v; 
		for (int j = 0; j <= 1000; ++j) {
			last[j] = 0.0;
		}
 		
		for (int i = 1; i <= n; ++i) {
			fin >> el[i];
		}

		sort(el + 1, el + n + 1);
		long double chx = 1.0;
		for (int i = n; i; --i) {
			// iau elementul asta cu 2 ^ 
			chx /= 2.0;
			for (int val = 0; val <= 1000; ++val) {
				now[val] = last[val] / 2.0;
				now[val % el[i]] += last[val] / 2.0;
			}
 			now[0] += 1.0 * int(v / el[i]) * chx;
 			for (int val = 1; val < el[i]; ++val) {
				now[val] += 1.0 * int((v - val + el[i]) / el[i]) * chx;
			}

			for (int val = 0; val <= 1000; ++val) {
				last[val] = now[val];
			}
			
/*			cerr << fixed << setprecision(3) << chx << "\t\t";
			for (int val = 0; val < 6; ++val) {
				cerr << fixed << setprecision(3) << last[val] << '\t';
			}
			cerr << '\n';*/
		}
		fout << fixed << setprecision(9) << last[0] << '\n';
	}
	return 0;
}
