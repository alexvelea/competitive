//Problem C from Codeforces Round coci2014round6
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

int main() {
	int n, m; cin >> n >> m;
    vector<string> txt(n), rez(n);
	for (int i = 0; i < n; ++i) {
		string _txt;
		cin >> _txt;
		txt[i] = (_txt);
	}

	int mn = n + 1;

	for (int c = 0; c < m; ++c) {
		int l = n - 1;
		int lastG = n;
		int firstX = -inf;
		for (; l >= 0; --l) {
			if (txt[l][c] == '#')
				lastG = l;
			if (txt[l][c] == 'X' and firstX == -inf)
				firstX = l;
		}

	   mn = min(mn, lastG - firstX);
   }
   --mn;
 	
	for (int i = 0; i < n; ++i)
		rez[i] = string(m, '.');
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
	 if (txt[i][j] == '#')
		 rez[i][j] = '#';
	 if (txt[i][j] == 'X')
		 rez[i +mn][j] = 'X';
}
  }

	for (auto &itr : rez)
		cout << itr << '\n';
	return 0;
}
