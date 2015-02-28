#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

ifstream in("urat.in");
ofstream out("urat.out");

const int Mod = 543217, kMaxN = 500005;

int fact[kMaxN / 2], el[kMaxN];

int main() {
	fact[1] = 1;
	fact[0] = 1;
 	for (int i = 2; i < kMaxN / 2; ++i) 
		fact[i] = (1LL * fact[i - 1] * i) % Mod;

	int n;
	in >> n;

 	if (n & 1) {
		int64 rez = 0;
		int st = n / 2;
		int dr = st + 2;
		for (int i = 1; i + 2 <= n; i += 2) {
			el[i] = st;
 			el[i + 1] = dr;
			st--;
			dr++;
		}
		el[n] = (n / 2) + 1;

        for (int i = 1; i < n; ++i)
			rez += abs(el[i] - el[i + 1]);

		out << rez << '\n';
		out << (1LL * 4 * fact[n / 2] * fact[n / 2 - 1]) % Mod << '\n';
		for (int i = 1; i <= n; ++i)
			out << el[i] << ' ';
		out << '\n';
	} else {
		int64 rez = 0;
		int st = n / 2;
		int dr = n;
		for (int i = 1; i <= n; i += 2) {
			el[i] = st;
			el[i + 1] = dr;
			st--;
			dr--;
		}
		for (int i = 1; i < n; ++i)
			rez += abs(el[i] - el[i + 1]);

		out << rez << '\n';
		out << (1LL * 2 * fact[n / 2 - 1] * fact[n / 2 - 1]) % Mod << '\n';
		for (int i = 1; i <= n; ++i)
			out << el[i] << ' ';
		out << '\n';
	}
	return 0;
}
