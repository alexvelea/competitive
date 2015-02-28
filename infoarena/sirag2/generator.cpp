#include <cmath>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
	srand(time(NULL));
	for (int t = 0; t < 100; ++t) {
		int n = 100, sigma = 3;

		ofstream out("sirag2.in");
		out << "10\n";
		for (int p = 0; p < 10; ++p) {
			out << n << ' ' << rand() % int(sqrt(n)) + 1 << '\n';
			for (int i = 1; i <= n; ++i) {
	        	int chx = rand() % 10;
				if (chx < 5) 
					out << '*';
				else
				out << char('a' + (rand() % sigma));
			}
			out << "\n";
		}

		out.close();

		system("./sirag2");
		system("./brut");

		ifstream in("sirag2.out");
		ifstream in2("sirag22.out");
	
		string a, b, aux;
		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;

		in.close();
		in2.close();

		if (a != b) {
			cerr << "Gresit la " << t;
			return 0;
		}
		if (t % 5 == 0)
			cerr << t << '\n';
	}
	return 0;
}
