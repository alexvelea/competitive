#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

int main() {
	
    srand(time(NULL));
	int t = 0;

	while (t <= 1000) {
		++t;
		int n, m, k;
		n = rand() % 100 + 10;
		m = rand() % 100000 + 1;
		k = rand() % 10000 + 1;

		ofstream out("ninja.in");
		out << n << ' ' << m << ' ' << k << '\n';
		for (int i = 1; i <= n; ++i) {
			int x = rand() % m;
			x++;
			int d = rand() % (min(m - x + 1, x));
			out << x - d + 1<< ' ' << x + d - 1<< '\n';
		}
		for (int i = 1; i <= k; ++i) {
			int a = rand() % m, b = rand() % m;
			if (a > b)
				swap(a, b);
			a++;
			b++;
			out << a << ' ' << b << '\n';
		}
		out.close();

		system("./ninja");
		system("./brut");

		ifstream inA("ninja.out");
		ifstream inB("ninja2.out");

		int64 A = 0, B = 0, x;
		while (inA >> x) {
			A += x;
		}
		while (inB >> x) {
			B += x;
		}
		if (A != B)
			cerr << "Bug\t" << t << '\n';

		if (t % 100 == 0)
			cerr << t << '\n';

		inA.close();
		inB.close();
	}
}
