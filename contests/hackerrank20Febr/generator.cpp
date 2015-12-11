#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
	srand(time(NULL));
	const int t = 50;
	const int n = 100, q = 1000;
	const int kMaxVal = 1000;
	for (int T = 0; T < t; ++T) {
		ofstream out("library.in");
		out << "10\n";
	for (int p = 0; p < 10; ++p) {
		out << n << '\n';
		for (int i = 1; i <= n; ++i)
			out << (rand() % kMaxVal) + 1 << ' ';
		out << '\n';
		out << q << '\n';
		for (int i = 1; i<= q; ++i) {
			int t = rand() % 10;
			if (t < 3) {
            	int x = rand() % n, y = rand() % n;
				x++;
				y++;
				if (x > y)
					swap(x, y);
				int poz = rand() % (y - x + 1);
				poz++;
				out << "0 " << x << ' ' << y << ' ' << poz << '\n';
			} else {
				int x = rand() % n + 1;
				int val = rand() % kMaxVal + 1;
				out << "1 " << x << ' ' << val << '\n';
			}
		}
	}
		out.close();
		system("./library");
		system("./brut");

		string A, B, aux;
		ifstream in("library.out");
		ifstream in2("library2.out");
		while (in >> aux) {
			A += aux;
			A += ' ';
		}
		while (in2 >> aux) {
			B += aux;
			B += ' ';
		}
		if (A != B) {
			return 0;
		}
		cerr << T << '\n';
	}
	return 0;
}
