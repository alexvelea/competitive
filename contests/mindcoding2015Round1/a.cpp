//Problem A from Codeforces Round mindcodingRound1
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
	int t;
    cin >> t;
	for (int i = 1; i <= t; ++i) {
		bool ok = false;
		string txt;
		cin >> txt;
		if (txt[0] == txt[3] and txt[1] == txt[4])
			ok = true;
		if (txt[0] == txt[4] and txt[1] == txt[3])
			ok = true;
		if (txt[3] == '0' and txt[4] == '0')
			ok = true;
		if (txt[0] + 1 == txt[1] and txt[1] + 1 == txt[3] and txt[3] + 1 == txt[4])
			ok = true;
		if (txt[0] != '0') {
			int x = (txt[0] - '0') * 1000 + (txt[1] - '0') * 100 + (txt[3] - '0') * 10 + (txt[4] - '0');
 			for (int j = 0; j <= 20; ++j)
				if ((1 << j) == x)
					ok = true;
		}

        int x = (txt[0] - '0') * 10 + txt[1] - '0';
		int y = (txt[3] - '0') * 10 + txt[4] - '0';
		if (0 <= x and x < 24)
			;
		else
			ok = false;
		if (0 <= y and y < 60)
			;
		else
			ok = false;

		if (ok) 
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
