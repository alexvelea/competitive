//Problem A from Codeforces Round memsql
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;
char na[8][10] = {"vaporeon", "jolteon", "flareon", "espeon", "umbreon", "leafeon", "glaceon", "sylveon"};

int main() {
	int l;
	char txt[10];
	cin >> l >> txt;
	for (int i = 0; i < 8; ++i) {
		if (l != int(strlen(na[i])))
			continue;
		bool ok = true;
		for (int j = 0; j < l; ++j)
			if (txt[j] != '.' and txt[j] != na[i][j]) {
				ok = false;
				break;
			}
		if (ok) {
			cout << na[i];
			return 0;
		}
	}
	return 0;
}
