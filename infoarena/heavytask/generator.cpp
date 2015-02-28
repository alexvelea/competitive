#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

ofstream out("heavy.in");

int main() {
	out << "5\n";
	srand(time(NULL));
	int primes[5] = {2, 3, 5, 7, 11};
	int p[5] = {0};
	int n = 20;
	for (int i = 0; i < 5; ++i) {
		out << n << '\n';
		for (int j = 0; j < n; ++j) {
			double remain = log(10) * 16;
			for (int l = 0; l < 5; ++l) {
				if (int(remain / log(primes[l])) == 0) {
					p[l] = 0;
					continue;
				}
				p[l] = rand() % int(remain / log(primes[l]));
				remain -= log(primes[l]) * p[l];
			}
			long long rez = 1;
			for (int l = 0; l < 5; ++l) {
				while (p[l]) {
					--p[l];
					rez = 1LL * rez * primes[l];
				}
			}
			out << rez << ' ' ;
		} 
	}
	return 0;
}
