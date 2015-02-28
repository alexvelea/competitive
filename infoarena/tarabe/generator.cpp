#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
	srand(time(NULL));

	for (int t = 1; t <= 1; ++t) {
		const int n = 200000;
		const int k = 1000000000;
		const int kMaxVal = 300;

		ofstream out("tarabe.in");
		out << n << ' ' << k << '\n';
		for (int i = 1; i <= n; ++i) {
			out << rand() % kMaxVal + 1 << ' ' << rand() % kMaxVal + 1 << '\n';
		}
		out.close();

		system("./tarabe");
		system("./brut");

		string a, b, aux;
		ifstream in("tarabe.out");
		ifstream in2("tarabe2.out");

		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;
		
		if (a != b) 
			cerr << "Problem\t" << t << '\n';
		if (t % 10 == 0)
			cerr << t << '\n';

	}
	return 0;
}
