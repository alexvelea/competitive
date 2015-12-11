//Problem D from Codeforces Round coci2014round6
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

int rez[100005];
bool bad[100005];

int main() {
    int n, k; cin >> n >> k;
	int step = 1;
	for (; step * step < n; ++step)
		;
	if (step > k) {
		cout << "-1\n";
	} else {
		int left = n, act = 0;
		for (int i = 0; act + left != k and i <= step; ++i) {
			for (int j = (i + 1) * step; j > i * step and act + left != k; --j) {
				rez[++rez[0]] = j;
				bad[j] = true;
				--left;
				if (j - 1 == (i * step)) {
					++act;
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			if (not bad[i]) {
				rez[++rez[0]] = i;
			}
		for (int i = 1; i <= n; ++i) {
			cout << rez[i] << ' ' ;
		}
	}
	return 0;
}
