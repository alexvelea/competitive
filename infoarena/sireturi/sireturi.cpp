#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 7505, MOD = 9901;

ifstream in("sireturi.in");
ofstream out("sireturi.out");

int fib[kMaxN], primes[kMaxN], nr, r[kMaxN], ap[kMaxN];

int main() {
	for (int i = 2; i <= kMaxN; ++i) {
		if (fib[i] == 0) {
			fib[i] = i;
			for (int j = i * i; j < kMaxN; j += i) {
				fib[j] = i;
			}
			primes[i] = ++nr;
		}
	}
	int rez;
	r[0] = 1;
	r[1] = 1;
	for (int i = 2; i < kMaxN; ++i) {
		rez = 1;
		int x = i;
		while (x != 1) {
			ap[primes[fib[x]]] += 2;
			x /= fib[x];
		}
		rez = 1;
		for (int j = 1; j <= nr; ++j) 
			rez = (rez * (ap[j] + 1)) % MOD;
		r[i] = rez;
	}
	int t;
	in >> t;
	while (t--) {
		int n;
		in >> n;	
		n--;
		out << r[n] << '\n';
	}
	return 0;
}
