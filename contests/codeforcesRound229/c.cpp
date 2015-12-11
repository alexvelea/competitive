//Problem #C from Codeforces 229
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second

const int inf = 0x3f3f3f3f, kMaxN = 100005;

string el;
int sum_p[15][kMaxN], nr[15], sum[kMaxN];

int main() {
	int n, k, w;
 	cin >> n >> k >> w;
	cin >> el;
	for (int i = 1; i <= n; ++i) {
		int e = (el[i - 1] == '1');
		sum_p[i % k][++nr[i % k]] = e;
		sum[i] = sum[i - 1] + e;
	}
	for (int i = 0; i < k; ++i)
		for (int j = 1; j <= nr[i]; ++j)
	    	sum_p[i][j] += sum_p[i][j - 1];
	
	while (w--) {
		int st, dr;
		int rez = 0;
		cin >> st >> dr;
 		rez = sum[dr] - sum[st - 1];
		int c = dr % k;
		st += k - 1 + k - 1;
		dr += k - 1;
		dr /= k;
		st /= k;
		st--;
		rez += (dr - st);
		rez -= 2 * (sum_p[c][dr] - sum_p[c][st]);
		cout << rez << '\n';
	}
    return 0;
}

