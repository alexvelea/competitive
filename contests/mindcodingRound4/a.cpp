//Problem a from mindcodingRound4
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

int el[100005];
int rez[105][105];

int main() {
	ios::sync_with_stdio(false);
 	int n; cin >> n;
	for (int i = 1; i <= n * n; ++i) {
		cin >> el[i];
	}
	sort(el + 1, el + n * n + 1);
	reverse(el + 1, el + n * n + 1);
	for (int i = 1; i <= n; ++i) {
		rez[i][i] = el[i];
	}
	for (int l = 1, c = 1, i = n + 1; i <= n * n; ++i, ++c) {
		if (l == c) {
			++c;
		}
		if (c == n + 1) {
			c = 1;
			l++;
		}
		rez[l][c] = el[i];
	}
	for (int i = 1; i <= n; ++i, cout << '\n') 
		for (int j = 1; j <= n; ++j) {
			cout << rez[i][j] << ' ';
		}

	return 0;
}
