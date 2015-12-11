//Problem #B from Codeforces 229
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int A[kMaxN], B[kMaxN];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> A[i];
	for (int i = 1; i <= n; ++i)
		cin >> B[i];
	int64 rez = 0;
	for (int i = 1; i <= n; ++i) {
		if (2 * A[i] < B[i] or B[i] == 1)
			rez--;
		else {
			int a = B[i] / 2;
			int b = (B[i] + 1) / 2;
			rez += 1LL * a * b;
		}
	}
	cout << rez << '\n';
    return 0;
}

