//Problem #A from Codeforces 235
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

int main() {
	int n, x, sum = 0;
	cin >> n >> x;
 	for (int i = 1; i <= n; ++i) {
		int el;
		cin >> el;
		sum += el;
	}
	if (sum == 0)
		cout << '0';
	if (sum < 0) {
		sum *= -1;
	}
	if (sum > 0) {
		sum += x - 1;
		cout << sum / x;
	}
    return 0;
}

