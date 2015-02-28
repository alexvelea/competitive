//Problem #B from Codeforces 236
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 5005;

unordered_map<int, bool> is_bad;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int el[kMaxN], gcd_rez[kMaxN];

int get_score(int n) {
	int rez = 0;
	for (int d = 2; d * d <= n; ++d) {
		if (n % d == 0) {
			int val = 1;
			if (is_bad[d])
				val = -1;
			while (n % d == 0) {
				n /= d;
				rez += val;
			}
		}
	}
	if (n != 1) {
		if (is_bad[n])
			rez --;
		else
			rez++;
	}
	return rez;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) 
		cin >> el[i];
	for (int j = 1; j <= m; ++j) {
		int el;
		cin >> el;
		is_bad[el] = true;
	}

	gcd_rez[1] = el[1];
	for (int i = 1; i <= n; ++i)
		gcd_rez[i] = gcd(gcd_rez[i - 1], el[i]);
	
    for (int i = n; i; --i) {
		int x = get_score(gcd_rez[i]);
		if (x < 0) {
			for (int j = 1; j <= i; ++j) {
 				el[j] /= gcd_rez[i];   			
				gcd_rez[j] /= gcd_rez[i];
			}
		}
	}

	int rez = 0;

	for (int i = 1; i <= n; ++i)
		rez += get_score(el[i]);
	cout << rez << '\n';
	return 0;
}

