#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;
int main() {
	srand(time(NULL));
	for (int t = 0; t < 100; ++t) {
		int n = rand() % 100 + 10;
		int m = rand() % 100 + 10;
		int k = rand() % (n * m);
		const int kMaxVal = 200;
 		n = 300;
		m = 300;
//        n = m = 5;
//		k = rand() % 25;

		if (k == 0)
			k = 1;

		ofstream out("submatrix.in");
		out << n << ' ' << m << ' ' << k << '\n';

		for (int i = 1; i <= n; ++i, out << '\n')
			for (int j = 1; j <= m; ++j)
				out << rand() % kMaxVal << ' ';
		out.close();

		system("./submatrix");
//		system("./brut");

		string a, b, aux;
		ifstream in("submatrix.out");
		ifstream in2("submatrix2.out");
	
		in >> a;
		in2 >> b;
		if (a != b) {
			cerr << "Problem\t" << t;
			return 0;
		}
		cerr << t << '\n';
		in.close();
		in2.close();
	}
	return 0;
}
