//Problem #B from Codeforces MindcodingFinal1
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

int edge[105][105];

int main() {
	int k, a, b;
 	cin >> k >> a >> b;
	if (a != 1 and b != 1) {
    	cout << "Impossible\n";
	} else {
		if (a == 1 and b == 1) {
	   		if (k <= 3) {
				cout << "Impossible\n";
				return 0;
			}

			cout << k - 1 << '\n';
			for (int i = 1; i < k; ++i)
				cout << i << ' ' << i + 1 << '\n';
			return 0;
	 	}

		int n = max(a, b);
 		for (int i = n; i < k; ++i)
			edge[i][i + 1] = edge[i + 1][i] = true;
		if (a == 1) {
			for (int i = 1; i <= n; ++i)
				for (int j = i + 1; j <= n; ++j)
					edge[i][j] ^= 1;
		}
		int m = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				m += edge[i][j];
		cout << m << '\n';
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (edge[i][j])
				cout << i << ' ' << j << '\n';
	}
    return 0;
}

