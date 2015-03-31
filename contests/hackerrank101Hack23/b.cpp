//Problem b from hackerrank101Hack23
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 1000005;

int el[kMaxN];

int main() {
	ios::sync_with_stdio(false);
 	int t; cin >> t;
	while (t--) {
		string txt; cin >> txt;
		txt += '#';
		int n = 0, current = 0;
		for (int i = 0; i + 1 < int(txt.size()); ++i) {
			current++;
			if (txt[i] != txt[i + 1]) {
				el[++n] = current;
				current = 0;
			}
		}
        
		if (n <= 2) {
			cout << n << '\n';
			continue;
		}

		bool find1 = false;

		for (int i = 2; i < n; ++i) {
			if (el[i] == 1)
				find1 = true;
		}

		if (find1 and n >= 4) {
			cout << n - 2 << '\n';
			continue;
		}

		if (el[1] == 1 or el[n] == 1) {
			find1 = true;
		}

		if (find1) {
			cout << n - 1 << '\n';
			continue;
		}

		cout << n << '\n';
	}
	return 0;
}
