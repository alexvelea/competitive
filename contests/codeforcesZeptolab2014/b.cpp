//Problem #B from Codeforces zepto
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f;

int rez[2005];

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			char c;
			cin >> c;
			if (c == 'U' and i % 2 == 1)
				rez[j]++;
			if (c == 'R' and i + j - 1 <= m)
				rez[i + j - 1]++;
			if (c == 'L' and j - i + 1 >= 1)
				rez[j - i + 1]++;
		}
	for (int i = 1; i <= m; ++i)
		cout << rez[i] << ' ';
    return 0;
}

