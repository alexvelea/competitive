//Problem #A from Codeforces 229
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

const int inf = 0x3f3f3f3f;

int A[105], B[105];

int main() {
	int n, rezA = 0, rezB = 0;
 	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int a, b;
		cin >> a >> b;
		if (A[a] == 0) {
	    	A[a] = 1;
			rezA++;
		}
		if (B[b] == 0) {
			B[b] = 1;
			rezB++;
		}
	}
	cout << min(rezA, rezB);
    return 0;
}

