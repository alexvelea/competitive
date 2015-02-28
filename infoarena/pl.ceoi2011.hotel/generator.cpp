#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;

ifstream in;
ofstream out;

string read(ifstream &in) {
	string aux, rez;
	while (in >> aux) {
		rez += aux;
		rez += ' ';
	}
	in.close();
	return rez;
}

int main() {
	srand(time(NULL));
	for (int t = 1; t <= 1000; ++t) {
        out.open("input.txt");
        int n = 200, m = 300, o = 0;
        out << n << ' ' << m << ' ' << o << '\n';
		
		int lastCost = 0, lastNrPerson = 0;
		for (int i = 1; i <= n; ++i) {
			lastCost += rand() % 1000;
			lastNrPerson += rand() % 10;
			out << lastCost << ' ' << lastNrPerson << '\n';
		}

		for (int i = 1; i <= m; ++i) {
			out << rand() % (1000 * n / 2) + 1 << ' ' << rand() % (10 * n / 2) + 1 << '\n';
		}
		
		out.close();

		system("./pl.ceoi2011.hotel");
		in.open("output.txt");
		string A = read(in);

		system("./official");
		in.open("output.txt");
		string B = read(in);
		
		if (A != B) {
			cerr << "Gresit \t" << t << '\n';
			return 0;
		}

		if (t % 10 == 0)
			cerr << t << "!!!!\n";
	}
	return 0;
}

