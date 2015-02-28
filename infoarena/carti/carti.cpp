#include <cmath>
#include <cassert>

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

ifstream in("carti.in");
ofstream out("carti.out");

const int inf = 0x3f3f3f3f;

int el[13];

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, k;
		in >> n >> k;
		for (int i = 0; i < n; ++i) {
			char c;
			in >> c;
			if (c == '1') {
				el[i] = 10;
				in >> c;
				continue;
			}
			if (c == 'A') {
				el[i] = 1;
				continue;
			}
			if (c == 'J') {
				el[i] = 11;
				continue;
			}
			if (c == 'Q') {
				el[i] = 12;
				continue;
			}
			if (c == 'K') {
				el[i] = 13;
				continue;
			}
			el[i] = c - '0';
		}
		sort(el, el + n);
		
	}
    return 0;
}
