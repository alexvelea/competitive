//Problem #C from Codeforces code_strike_2014_round_1
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int 
inf = 0x3f3f3f3f;


string txt[100005];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> txt[i];
	int l = txt[0].size();
	for (int i = 0; i < l; ++i) {
		char c = txt[0][i];
		bool ok = true;
		for (int j = 1; j < n; ++j) {
			if (c == '?')
				c = txt[j][i];
			else
				if (txt[j][i] != c and txt[j][i] != '?')
					ok = false;
		}
		if (ok) {
			if (c == '?')
				cout << 'a';
			else
				cout << c;
		} else
			cout << '?';
	}
    return 0;
}

