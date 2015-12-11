#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ofstream out;
ifstream in;

string Read() {
	string txt, aux;
	while (in >> aux) {
		txt += aux;
		txt += '#';
	}
	in.close();
	return txt;
}


int main() {
	srand(time(NULL));
	int el[10] = {1, 1, 5, 2, 2, 2, 2, 2, 3, 4};
	for (int t = 1; t <= 1000; ++t) {
		int n = 10000;
		int q = 2000;
		out.open("vlad.in");
		out << n << ' ' << q << '\n';
		for (int i = 1; i <= n; ++i) {
        	out << el[(rand() + i) % 10] << ' ';
		}
		out << '\n';
		for (int i = 1; i <= q; ++i) {
			int x = rand() % n + 1, y = rand() % n + 1;
			if (x > y)
				swap(x, y);
			out << x << ' ' << y << '\n';
		}
		out.close();
 		string a, b;

		system("./vlad");
		in.open("vlad.out");
		a = Read();

		system("./brut");
		in.open("vlad2.out");
		b = Read();

		if (a != b) {
			cerr << "Gresit";
			return 0;
		}
		cerr << t << '\n';
	}
	return 0;
}

