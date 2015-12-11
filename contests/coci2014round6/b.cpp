//Problem B from Codeforces Round coci2014round6
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int nr[15][4];
int choice[8];

int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d-%d-%d", &nr[i][0], &nr[i][1], &nr[i][2]);
	}

	int m; scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		string _choice;
		cin >> _choice;
		int ch = 0;
		for (auto itr : _choice) {
			if (itr == 'O')
				ch |= 1;
			if (itr == 'V')
				ch |= 2;
			if (itr == 'N')
				ch |= 4;
		}
		choice[ch]++;
	}

	for (int i = 0; i < n; ++i) {
		bool ok = true;
		for (int st = 1; st < 8; ++st) {
			int require = 0;
			for(int j = 0; j < 3; ++j) {
				if (st & (1 << j)) {
					require += nr[i][j];
				}
			}
			for (int j = 0; j < 8; ++j) {
				if (st & j) {
					require -= choice[j];
				}
			}
			if (require > 0) {
				ok = false;
			}
		}
		if (ok) {
			printf("DA\n");
		} else {
			printf("NE\n");
		}
	}
	return 0;
}
