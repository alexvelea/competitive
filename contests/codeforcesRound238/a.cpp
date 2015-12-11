//Problem #A from Codeforces 238
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

string sol;

const int kBufferSize = 10000;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (cin.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

void cit(int &n) {
	verf;
	for (; not char_ok; verf)
		;
	
	bool sign = false;
	if (BufferC == '-') {
		verf;
		sign = true;
	}
    
	n = 0;
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, sum = 0;
//    cit(n);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int x;
//            cit(x);
			cin >> x;
			if (i == j)
				sum ^= x;
		}
	int q;
//    cit(q);
	cin >> q;
	while (q--) {
		int t;
//        cit(t);
		cin >> t;
		if (t == 1 or t == 2) {
			int x;
//            cit(x);
			cin >> x;
			sum ^= 1;
		} else {
//			cout << sum;
			sol += '0' + sum;
		}
	}
	cout << sol << '\n';
    return 0;
}

