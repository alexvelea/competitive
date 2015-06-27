//Problem b from coci2014Round7
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

int64 rez[kMaxN];
int el[kMaxN], where[kMaxN];

int main() {
	ios::sync_with_stdio(false);
    int n, k; cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> el[i];
		el[i]--;
		where[el[i]] = i;
	}
	int64 Rez = where[0];
	int poz = where[0];
	for (int i = 1; i <= n; ++i) {
		int el = i % n;
		int add = (where[el] + n - poz) % n;
		rez[i] = rez[i - 1] + add;
		poz = where[el];
	}
	k--;
	Rez += 1LL * rez[n] * (k / n);
	Rez += rez[(k % n)];
	cout << Rez << '\n';
	return 0;
}
