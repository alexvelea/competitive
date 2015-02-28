#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;
int main() {
	for (int t = 0; t < 100; ++t) {
		const int n = 30, m = 200;

		ofstream out("puncte.in");
		out << n <<  ' ' << m << '\n';
		for (int i = 1; i <= n; ++i) {
			out << rand() % 100 - 50 << ' ' << rand() % 50 - 20 << '\n';
		}
		for (int i = -(m / 2); i + (m / 2) < m; ++i)
			out << i << '\n';

		out.close();

		system("./brut");
		system("./puncte");

		ifstream in("puncte.out");
		ifstream in2("date.out");

		string a, b, aux;
		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;

		if (a != b) {
			cerr << "Gresit " << t << '\n';
			return 0;
		}
		if (t % 5 == 0)
			cerr << t << '\n';
	}
 	return 0;
}

