//Problem A from Codeforces Round facebookHackerCup2015Qualification
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

int z[10];

ifstream in("input.txt");
ofstream out("output.txt");


int main() {
	z[0] = 1;
	for (int i = 1; i <= 8; ++i)
		z[i] = 10 * z[i - 1];

	int t;
    in >> t;
	for (int T = 1; T <= t; ++T) {
   		string txt;
		in >> txt;
		reverse(txt.begin(), txt.end());
		int n = txt.size(), init = 0;
		for (int i = 0; i < n; ++i) {
			init += z[i] * (txt[i] - '0');
		}
		
        int mn = init, mx = init;

		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				int aux = init - z[i] * (txt[i] - '0') - z[j] * (txt[j] - '0')
					+ z[j] * (txt[i] - '0') + z[i] * (txt[j] - '0');
				if (aux >= z[n - 1]) {
					if (aux > mx) {
						mx = aux;
					}
					if (aux < mn) {
						mn = aux;
					}
				}
			}
		}

		out << "Case #" << T << ": " << mn << ' ' << mx << '\n';
	} 
	return 0;
}
