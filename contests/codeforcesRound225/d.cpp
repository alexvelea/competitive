#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second

const int MOD = 1000000007;
const int kMaxN = 1005, kMaxS = 10005;

int ways[2][kMaxS];
int el[kMaxN];

void mod(int &a) {
	if (a >= MOD)
		a -= MOD;
}

int main() {
	int n, rez = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	int sum = 0;
	for (int dr = n; dr; --dr) {
		for (int i = 0; i <= sum; ++i) {
 			ways[0][i] = ways[1][i];
			ways[1][i] = 0;
		}
		ways[0][0]++;
		for (int i = 0; i <= sum; ++i) {
			ways[1][i + el[dr]] += ways[0][i];
			ways[1][abs(i - el[dr])] += ways[0][i];
			mod(ways[1][i + el[dr]]);
			mod(ways[1][abs(i - el[dr])]);
		}
		sum += el[dr];
		rez += ways[1][0];
		mod(rez);
	}
	cout << rez << '\n';
	return 0;
}
