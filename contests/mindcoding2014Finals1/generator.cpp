#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ifstream in;
ofstream out;

string read() {
	string rez, val;
	while (in >> val) {
		rez += val;
		rez += '$';
	}
	in.close();
	return rez;
}

int main() {
	srand(time(NULL));
	for (int t = 0; t < 1; ++t) {
		int n = 100000;
		int q = 100000;
		out.open("date.in");
/*		out << n << ' ' << q * (100 + n) << '\n';

		while (q--) {
			for (int i = 0; i < 100; ++i) {
				int x = rand() % n + 1, y = rand() % n + 1;
				if (x > y)
					swap(x, y);
				out << "1 " << x << ' ' << y << '\n';
			}
			for (int i = 1; i <= n; ++i)
				out << "2 " << i << '\n';
		}*/
		out << n << ' ' << q << '\n';
		for (int i = 1; i <= q; i += 4) {
			int x = rand() % 100 + 1, y = rand() % 100 + 1;
			out << "1 " << x << ' ' << n - y << '\n';
			out << "2 " << n / 2 << '\n';
			out << "2 " << n / 2 + rand() % 100 << '\n';
			out << "2 " << n / 2 - rand() % 100 << '\n';
		}

		system("./c");
		system("./buhi");

		string a, b;

		out.close();
 		in.open("date.out");
		a = read();
		in.open("date2.out");
		b = read();
		if (a != b) {
			cerr << t << " ERROR\n";
			return 0;
		}
		if (t % 5 == 0)
			cerr << t << '\n';
	}
	return 0;
}
