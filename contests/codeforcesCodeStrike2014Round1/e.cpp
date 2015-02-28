//Problem #E from Codeforces code_strike_2014_round_1
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kMaxN= 1000005;

bool is_letter(char c) {
	if (c >= 'a' and c <= 'z')
		return true;
	return false;
}

string txt;
int rez[kMaxN], rez2[kMaxN];

int main() {
	cin >> txt;
	int n = txt.size();
	int v = 0;
   	for (int i = 0; i < n; ++i) {
		if (txt[i] == '@') {
			rez[i] = v;
			v = 0;
			continue;
		}
		if (txt[i] == '.')
			v = 0;
		if (txt[i] >= 'a' and txt[i] <= 'z')
			++v;
	}
	v = 0;
	for (int i = n - 1; i >= 0; --i) {
 		if (txt[i] == '.') {
			rez2[i] = v;
			v = 0;
			continue;
		}

		if (txt[i] >= 'a' and txt[i] <= 'z') {
			++v;
			continue;
		}

 		v = 0;
	}
	int64 R = 0;
	for (int i = 0; i < n; ++i) {
		if (txt[i] == '@' and i + 2 < int(txt.size())) {
			bool b = is_letter(txt[i + 1]), ok = true;
			int r = rez[i];
			int st = i;
			for (i++; txt[i] != '.' and i < int(txt.size()); ++i) {
				if (txt[i] == '_')
					ok = false;
				if (txt[i] == '@') {
					ok = false;
					--i;
					break;
				}
				if (is_letter(txt[i] != b))
					ok = false;
			}
			if (i == st + 1)
				continue;
			if (ok)
				R += 1LL * r * rez2[i];
		}
	}
	cout << R << '\n';
    return 0;
}

