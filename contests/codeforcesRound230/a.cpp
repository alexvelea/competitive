//Problem #A from Codeforces 230
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

const int inf = 0x3f3f3f3f;

int sqr(int64 a) {
	int b = sqrt(a);
	b-= 2;
	if (b < 0)
		b = 0;
	while (1LL * b * b <= a)
		++b;
	--b;
	return b;
}

int main() {
	int n, rez = 0;
	n = 40000000;
	int Dr = n;
 	int64 mx = 1LL * n * n;

	for (int St = 0; St < n; ) {
		rez++;
		St = sqr(mx - 1LL * Dr * Dr);
		St++;
		Dr = sqr(mx - 1LL * St * St);
	}
	
	if(n == 0)
		cout << "1\n";
	else {
		if (n == 1)
			cout << "4\n";
		else
			cout << (2 * n - rez) * 4 << '\n';
	}

    return 0;
}

