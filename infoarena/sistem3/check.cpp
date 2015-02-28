#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 100005;

int Mod, n;
int sol[kMaxN], rez[kMaxN];

int mod(int a) {
	while (a < 0)
		a += Mod;
	while (a >= Mod)
		a -= Mod;
	return a;
}

int main() {
	ifstream in2("sistem3.out");
	ifstream in1("sistem3.in");
	in1 >> n >> Mod;
	for (int i = 1; i <= n; ++i) {
		in2 >> sol[i];
	}
	for (int i = 1; i <= n; ++i) {
		int a, b, c;
		in1 >> a >> b >> c;
 		rez[a] += (1LL * mod(sol[a] - sol[b]) * c) % Mod;
		rez[b] += (1LL * mod(sol[b] - sol[a]) * c) % Mod;
	}
	for (int i = 1; i <= n; ++i) {
		int a;
		in1 >> a;
		if (a != (rez[i] % Mod))
			cerr << "Bad\n";
	}
	cerr << "Ok\n";
	return 0;
}
