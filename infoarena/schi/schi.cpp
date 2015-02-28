#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("schi.in");
ofstream out("schi.out");

const int inf = 0x3f3f3f3f, kMaxN = 30005;

int aib[kMaxN], rez[kMaxN], el[kMaxN];

void aib_update(int ind, int val) {
	while (ind < kMaxN) {
		aib[ind] += val;
		ind += ind & (-ind);
	}
}

int aib_search(int k) {
	int p = 1 << 15;
	int rez = 0;
	for (; p; p >>= 1)
		if (rez + p < kMaxN) {
			if (aib[rez + p] < k) {
				k -= aib[rez + p];
				rez += p;
			}
		}
	return rez + 1;
}

int main() {
 	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		in >> el[i];
		aib_update(i, +1);
	}

	for (int i = n; i; --i) {
		int r = aib_search(el[i]);
		aib_update(r, -1);
		rez[r] = i;
	}
	
	for (int i = 1; i <= n; ++i)
		out << rez[i] << '\n';
    return 0;
}
