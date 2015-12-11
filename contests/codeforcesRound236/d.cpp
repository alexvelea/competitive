//Problem #D from Codeforces 236
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

const int Mod = 1000000007, kMaxN = 1005;

int DP[kMaxN][kMaxN], rez[kMaxN][kMaxN];
int fact[2 * kMaxN];

const int kBufferSize = 1000005;
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

int pow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1)
			rez = (1LL * rez * a) % Mod;
		p /= 2;
		a = (1LL * a * a) % Mod;
	}
	return rez;
}

int comb(int n, int k) {
	if (k > n)
		swap(n, k);
	int rez = fact[n];
	rez = (1LL * rez * pow(fact[k], Mod - 2)) % Mod;
	rez = (1LL * rez * pow(fact[n - k], Mod - 2)) % Mod;
	return rez;
}

void mod(int &a) {
	if (a >= Mod)
		a -= Mod;
}

int main() {
	DP[0][0] = 1;
	for (int i = 1; i <= 1000; ++i) 
		for (int j = (i - 1) * (i) / 2; j <= 1000; ++j) {
			// in cate moduri putem sa il scriem pe j ca suma de i numere distincte
			DP[i][j] = DP[i - 1][j - i + 1];
			DP[i][j] += DP[i][j - i];
			mod(DP[i][j]);
		}

	fact[0] = fact[1] = 1;
	for (int i = 2; i < 2 * kMaxN; ++i)
		fact[i] = (1LL * fact[i - 1] * i) % Mod;
	for (int k = 1; k <= 1000; ++k) {
		for (int n = (k - 1) * (k) / 2; n <= 1000; ++n) {
        	for (int sum = (k - 1) * (k) / 2; sum <= n; ++sum) {
				int remaining = n - sum - (k - 1) - 1;
				if (remaining < 0)
					continue;
            	rez[k][n] += (1LL * ((1LL * fact[k] * (comb(k + remaining, k))) % Mod) * DP[k][sum]) % Mod;
				mod(rez[k][n]);
			}
		}
	}
    
	int t = 0;
	cit(t);
	while (t--) {
		int n, k;
		cit(n);
		cit(k);
		cout << rez[k][n] << '\n';
	}
	return 0;
}

