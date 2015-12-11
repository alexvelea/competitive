//Problem c @ 01-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

int k;

int mex(int x) {
	if (x == 0) {
		return 0;
	}
	if (k % 2 == 0) {
		if (x % 3 == 0) {
			return 0;
		} else if (x % 3 == 1) {
			return 1;
		}
		return 2;
	}

	if (x & 1) {
		if (x == 1 or x == 3) {
			return 1;
		} else {
			return 3;
		}
	} else {
		if (k % 2 == 0) {
			return 2;
		} else {
			int y = mex(x / 2);	
			int z = mex(x - 1);
			if (y != 0 and z != 0) {
				return 0;
			}
			if (y != 1 and z != 1) {
				return 1;
			}
			if (y != 2 and z != 2) {
				return 2;
			}
		}	
	}
}

int main() {
	int n; cin >> n >> k;
	int rez = 0;

	for (int i = 1; i <= n; i += 1) {
		int x; cin >> x;
		rez ^= mex(x);
	}
	if (rez) {
		cout << "Kevin";
	} else {
		cout << "Nicky";
	}
	return 0;
}
