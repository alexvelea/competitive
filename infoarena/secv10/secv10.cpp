//Problem secv10 from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("secv10.in");
ofstream out("secv10.out");

char txt[kMaxN], st[kMaxN], dr[kMaxN];
int prefix[kMaxN];

void makePrefix(char txt[]) {
	prefix[1] = 0;
	int n = strlen(txt);
	for (int i = 2; i < n; ++i) {
		prefix[i] = prefix[i - 1];
		while (txt[i] != txt[prefix[i] + 1] and prefix[i] != 0) {
			prefix[i] = prefix[prefix[i]];
		}

		if (txt[prefix[i] + 1] == txt[i]) {
			++prefix[i];
		}
	}
}

int main() {
	int t; in >> t;
	while (t--) {
		txt[0] = st[0] = dr[0] = ' ';
		in >> (txt + 1) >> (st + 1) >> (dr + 1);
 		makePrefix(txt);
		int n = strlen(txt);
		vector<int> startDr(n, 0);
		// make for dr
		for (int i = 1, k = 0, t = strlen(dr) - 1; i < n; ++i) {
			while (k != 0 and txt[i] != dr[k + 1]) {
				k = prefix[k];
			}
			
			if (txt[i] == dr[k + 1]) {
				++k;
			}

			if (k == t) {
				k = prefix[k];
				startDr[i]++;
			}
		}

		for (int i = n - 2; i >= 0; --i) {
			startDr[i] += startDr[i + 1];
		}

		int64 rez = 0;

		for (int i = 1, k = 0, t = strlen(st) - 1; i < n; ++i) {
			while (k != 0 and txt[i] != st[k + 1]) {
				k = prefix[k];
			}

			if (txt[i] == st[k + 1]) {
				++k;
			}

			if (k == t) {
				k = prefix[k];
				rez += startDr[i];
			}
		}

		out << rez << '\n';
	}
	return 0;
}
