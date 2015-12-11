//Problem b @ 01-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMod = 1e9 + 7, kMaxN = 1e6 + 6;

#define int64 long long

bool viz[kMaxN];
int perm[kMaxN];

int logPow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1) {
			rez = (1LL * rez * a) % kMod;
		}
		p /= 2;
		a = (1LL * a * a) % kMod;
	}
	return rez;
}

int nr[kMaxN], generator[kMaxN];

int main() {
	ios::sync_with_stdio(false);
	int p, k; cin >> p >> k;
	if (k == 0) {
		cout << logPow(p, p - 1) << '\n';
		return 0;
	}

	for (int i = 0, val = 0; i < p; i += 1) {
		perm[val] = i;
		val += k;
		if (val >= p) {
			val -= p;
		}
	}
	int nrPerm = 0;
	for (int i = 0; i < p; i += 1) {
		if (not viz[i]) {
			int p = i;
			nrPerm += 1;
			int count = 0;
			while (not viz[p]) {
				count += 1;
				viz[p] = true;
				p = perm[p];
			}
			cout << count << '\t';
			generator[count] += count;
			nr[count] += 1;
		}
	}
	cout << '\n';
	cout << nrPerm << '\n';
	for (int i = kMaxN - 1; i; i -= 1) {
		for (int j = 2 * i; j < kMaxN; j += i) {
			generator[j] += generator[i];
		}
	}

	int rez = 1;
	for (int i = 1; i < kMaxN; i += 1) {
		while (nr[i]) {
			rez = (1LL * rez * generator[i]) % kMod;
			nr[i] -= 1;
		}
	}
	cout << rez << '\n';
	return 0;
}
