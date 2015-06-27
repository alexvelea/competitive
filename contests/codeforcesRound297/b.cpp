//Problem b from codeforcesRound297
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

bool chx[200005];

int main() {
	ios::sync_with_stdio(false);
 	string txt; cin >> txt;
	int n = txt.size();
	int m; cin >> m;
	while (m--) {
		int st; cin >> st;
		st--;
       	chx[st] ^= 1;
	}
	for (int i = 1; i * 2 < n; ++i) {
		chx[i] ^= chx[i - 1];
	}
	for (int i = 0; i * 2 < n; ++i) {
		if (chx[i]) {
			swap(txt[i], txt[n - i - 1]);
		}
	}
	cout << txt;
	return 0;
}
