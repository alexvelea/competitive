#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
string to_str(int n) {
	string rez;
	rez = "000";
	int i = 2;
	while (n) {
		rez[i] = n % 10 + '0';
		n /= 10;
		--i;
	}
	return rez;
}

void to_char (string a, char c[]) {
	int i;
	for (i = 0; i < int(a.size()); ++i)
		c[i] = a[i];
	c[i] = '\0';
}

int main() {
	int n = 37;
	for (int i = 1; i <= n; ++i) {
		string nr = to_str(i);
		char in_file[10];
		char out_file[10];
		to_char(nr + ".in", in_file);
		to_char(nr + ".out", out_file);

		//
		//	De forma 001.in .. 001.out
		//
		//
		//
		ifstream f_in(in_file);
		ofstream f_out("input.txt");
		char c;
		while (1) {
			c = f_in.get();
			if (c == -1)
				break;
			f_out << c;
		}
		f_out.close();
		cerr << "Hello!\t";

		clock_t st = clock();
		system("./bp"); // executabilul!~!~!~!~!
		clock_t dr = clock();
		cerr << 1.0 * (dr - st) / CLOCKS_PER_SEC << '\n' << '\n';
		//
		// trebuie sa aiba input.txt si output.txt
		//
		ifstream a_in("output.txt");
		ifstream b_in(out_file);
		long long x = 0, y = 0;
		cerr << i << '\t';
		while (a_in >> x) {
			b_in >> y;
			if (x != y) {
				cerr << "Bad!\n";
				cerr << x << '\t' << y << '\n';
				break;
			}
		}
		cerr << "END";
		cerr << '\n';
	}
	return 0;
}
