//Problem #A from Codeforces 233
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

void print(int &q, int &w, int d) {
	int nr = 0;
	if (q) {
		--q;
		nr = d;
	} else {
		if (w == 0)
			return;
		--w;
		nr = d + 1;
	}
	for (int i = 1; i <= nr; ++i)
		cout << 'x';
}

int main() {
	int a, b;
	cin >> a >> b;

	int64 mx = - 1ll * b * b;
	int sol = 0;

	for (int i = 1; i <= a; ++i) {
		int64 rez = 1ll * (i - 1) + 1LL * (a - i + 1) * (a - i + 1);
		int w = b % (i + 1);
		int q = (i + 1) - w;
		int d = b / (i + 1);
		rez -= 1LL * q * d * d;
		rez -= 1LL * w * (d + 1) * (d + 1);
		if (rez > mx) {
			mx = rez;
			sol = i;
		}
	}
	cout << mx << '\n';
	int w = b % (sol + 1);
	int q = (sol + 1) - w;
	int d = b / (sol + 1);
	print(q, w, d);
	for (int i = 1; i < sol; ++i) {
		cout << 'o';
		print(q, w, d);
		--a;
	}
	for (int i = 1; i <= a; ++i) {
		cout << 'o';
	}
	print(q, w, d);
    return 0;
}

