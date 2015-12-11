//Problem #D from Codeforces 237
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int kMaxN = 1000005, Mod = 1000000007;

string txt;
int n;
int rez[kMaxN][3];

int main() {
	cin >> txt;
    n = txt.size();

	if (txt[0] == '*') {
		rez[0][2] = 1;
	}
	if (txt[0] == '2') {
		cout << '0';
		return 0;
	}
	if (txt[0] == '0') {
		rez[0][0] = 1;
	}
	if (txt[0] == '1') {
		rez[0][1] = 1;
	}
	if (txt[0] == '?') {
		rez[0][2] = 1;
		rez[0][1] = 1;
		rez[0][0] = 1;
	}
	for (int i = 1; i < n; ++i) {
		if (txt[i] == '?') {
			rez[i][2] = (rez[i - 1][1] + rez[i - 1][2]) % Mod;
			rez[i][1] = (rez[i - 1][0] + rez[i - 1][2]) % Mod;
			rez[i][0] = (rez[i - 1][0] + rez[i - 1][2]) % Mod;
		} else {
			if (txt[i] == '0') {
				rez[i][0] = rez[i - 1][0];
			}
			if (txt[i] == '1') {
				rez[i][0] = rez[i - 1][2];
				rez[i][1] = rez[i - 1][0];
			}
			if (txt[i] == '2') {
				rez[i][1] = rez[i - 1][2];
			}
			if (txt[i] == '*') {
				rez[i][2] = (rez[i - 1][1] + rez[i - 1][2]) % Mod;
			}
		}
	}
	cout << (rez[n - 1][0] + rez[n - 1][2]) % Mod;
	return 0;
}

