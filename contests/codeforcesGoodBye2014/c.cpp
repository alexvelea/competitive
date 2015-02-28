//Problem C from Codeforces Round good.bye.2014
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

const int inf = 0x3f3f3f3f, kMaxN = 1005;

int w[kMaxN], rez[kMaxN], ord[kMaxN];
bool first[kMaxN];

int main() {
    int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	for (int i = 1; i <= m; ++i) {
		cin >> ord[i];
	}

	int N = 1;
	for (int i = 1; i <= m; ++i) {
		if (first[ord[i]] == false) {
			rez[N++] = ord[i];
			first[ord[i]] = true;
		}
	}
	
	int64 Rez = 0;
	for (int i = 1; i <= m; ++i) {
		int itr = 1;
		for (; rez[itr] != ord[i]; ++itr) 
			Rez += w[rez[itr]];
		for (int j = itr; j; --j)
			rez[j] = rez[j - 1];
		rez[1] = ord[i];
	}

	cout << Rez << '\n';
	return 0;
}
