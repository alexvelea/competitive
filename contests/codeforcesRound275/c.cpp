//Problem C from Codeforces Round 2775
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int a[105], b[105];

int main() {
 	int n, s;
    cin >> n >> s;
	if (s == 0 and n == 1) {
		cout << "0 0";
		return 0;
	}
	if (s == 0 or s > 9 * n) {
	    cout << "-1 -1\n";
		return 0;
	}
	int sa, sb;
	sa = sb = s;
	for (int i = 0; i < n; ++i)
		a[i] = b[i] = 0;
	a[0] = b[0] = 1;
	sa--;
	sb--;
	for (int i = 0; i < n and sa; ++i) {
		while (sa and a[i] < 9) {
			a[i]++;
			sa--;
		}
	}

	for (int i = n - 1; i >= 0 and sb; --i) {
		while (sb and b[i] < 9) {
			b[i]++;
			sb--;
		}
	}

	for (int i = 0; i < n; ++i) 
		cout << b[i];
	cout << " ";
	
	for (int i = 0; i < n; ++i)
		cout << a[i];
	
	return 0;
}
