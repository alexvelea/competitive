#include <cstdlib>
#include <ctime>

#include <fstream>
#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));
	int n = 1000;
	int t = 10;
    
	const int kMaxVal = 2;

	for (int T = 1; T <= 100; ++T) {
    	ofstream out("zlego.in");
		out << t << '\n';
		for (int i = 1; i <= t; ++i) {
			out << n << '\n';
			for (int i = 1; i <= n; ++i) {
				int x = rand() % kMaxVal;
				out << x << ' ';
			}
			out << '\n';
			for (int i = 1; i <= n; ++i) {
				int x = rand() % 100000000;
				out << x << ' ';
			}
			out << '\n';
		}
		out.close();
		system("./brut");
		system("./zlego");

		string a, b, aux;
		ifstream in("zlego.out");
		ifstream in2("zlego2.out");

		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;

		if (a != b) {
			cerr << "Greseala la T = " << T << '\n';
			return 0;
		}
		if (T % 5 == 0)
			cerr << T << '\n';
	}
	return 0;
}
