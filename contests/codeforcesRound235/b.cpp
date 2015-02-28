//Problem #B from Codeforces 235
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

const int inf = 0x3f3f3f3f;

bool viz[4005];

int main() {
	int x, k;
	cin >> x >> k;
	viz[x] = 1;
	for (int i = 1; i <= k; ++i) {
		int t;
		cin >> t;
		t = 3 - t;
		for (int j = 1; j <=t; ++j) {
			int el;
			cin >> el;
			viz[el] = true;
		}
	}
	int rez = 0;
	for (int i = 1; i <= x; ++i) {
		if (viz[i] == false) 
			rez++;
	}
	int mx = rez;
	rez = 0;
	for (int i = 1; i <= x; ++i) {
		if (viz[i] == false) {
			rez++;
			viz[i + 1] = true;
		}
	}
	cout << rez << ' ' << mx << '\n';
    return 0;
}

