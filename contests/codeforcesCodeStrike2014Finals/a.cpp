//Problem #A from Codeforces code_strike_2014_finals
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define fi first
#define se second
#define int64 long long

map<char, bool> good;
string txt;

int main() {
	good['A'] = 1;
	good['I'] = 1;
	good['M'] = 1;
	good['O'] = 1;
	good['T'] = 1;
	good['U'] = 1;
	good['V'] = 1;
	good['W'] = 1;
	good['X'] = 1;
	good['Y'] = 1;
	good['H'] = 1;
    cin >> txt;
	int n = txt.size();
	bool ok = true;
	for (int i = 0; i < n; ++i) {
		if (txt[i] != txt[n - i - 1])
			ok = false;
		if (good[txt[i]] != 1)
			ok = false;
	}
	if (ok)
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}

