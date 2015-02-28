// ##################
// # iti denumesti sursa cum vrei tu ... dar trebuie sa ai neaparat 'exe' cu ea
// # iti pui numele la sursa pe linia 55
// # afisezi in date.out
// # citesti din aint_lazy_equal.in
// # ai grija sa faci in.close() si out.close() la final sa faca flush
// # succes :)
// ##################

#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
	srand(time(NULL));

	const int n = 1000, m = 10000, kMaxVal = 100000000;
	int nrBad = 0;

	for (int t = 0; t < 100; ++t) {
		ofstream out("aint_lazy_equal.in");
		out << n << ' ' << m << '\n';
		for (int i = 1; i <= n; ++i)
			out << rand() % 10 << ' ';
		out << '\n';
		for (int i = 0; i < m; ++i) {
			int t = rand() % kMaxVal;
			if (t < 6) {
				int x, y;
				x = rand() % n + 1;
				y = rand() % n + 1;
				if (x > y)
					swap(x, y);
				out << "2 " << x << ' ' << y << '\n';
			} else {
				int x, y;
				x = rand() % n + 1;
				y = rand() % n + 1;
				if (x > y)
					swap(x, y);				
 				int val = rand() % kMaxVal;
				int chx = rand() % 100;
				if (chx < 2)
					val = 0;
				out << "1 " << x << ' ' << y << ' ' << val << '\n';
			}
		}
		out.close();

		system("./aint_lazy_equal");
		system("./brut");

		string a, b, aux;

		ifstream in("aint_lazy_equal.out");
		ifstream in2("date.out");

		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;

		if (a != b) {
			cerr << "Error\n";
			++nrBad;
		}
		if (t % 5 == 0)
			cerr << t << '\n';

		in.close();
		out.close();
	}
	cerr << "\n\n######\n\n" << (100 - nrBad) << " ok din 100\n";
	return 0;
}
