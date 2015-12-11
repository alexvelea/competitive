//Problem #A from Codeforces 237
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

char el[305][305];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			cin >> el[i][j];
		}
	bool ok = true;
	char a = el[1][1];
	char b = el[2][1];
	for (int i = 1; i <= n; ++i) {
		if (el[i][i] != a)
			ok = false;
		if (el[i][n - i + 1] != a)
            ok = false;
	}
	if (a == b)
		ok = false;
	int nr = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (el[i][j] == b)
				++nr;
	if (nr != (n * n) - 2 * n + 1)
		ok = false;
	if (ok)
		cout << "YES\n";
	else
		cout << "NO\n";
    return 0;
}

