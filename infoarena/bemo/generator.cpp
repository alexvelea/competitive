#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

int el[1505 * 1505];

int main() {
	srand(time(NULL));
	const int n = 1000, m = 300;
	for (int t = 0; t < 100; ++t) {
		for (int i = 1; i <= n * m; ++i)
			el[i] = i;
		random_shuffle(el + 1, el + n * m + 1);

        ofstream out("bemo.in");
		out << n << ' ' << m << '\n';

		for (int i = 1, ind = 1; i <= n; ++i, out << '\n')
			for (int j = 1; j <= m; ++j, ++ind)
				out << el[ind] << ' ';

		out.close();
		system("./bemo");
		system("./brut");

		string aux, a, b;
		
		ifstream in("bemo.out");
		while (in >> aux)
			a += aux;
		in.close();

 		ifstream in2("bemo2.out");
		while (in2 >> aux)
			b += aux;
		in2.close();

		if (a != b)
			cerr << "Gresit\t" << t << '\n';
		if (t % 10 == 0)
			cerr << "###\t" << t << '\n';
	}
	return 0;
}
