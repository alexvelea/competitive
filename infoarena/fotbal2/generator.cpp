#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;
int main() {
    srand(time(NULL));
	for (int t = 1; t <= 100; ++t) {
		int n = 50000;
		int m = 50000;

		ofstream out("fotbal2.in");
		out << n << ' ' << m << '\n';
		for (int i = 1; i <= m; ++i) {
			int x = rand() % n + 1;
			int y = rand() % n + 1;
			while (x == y)
				y = rand() % n + 1;
			out << x << ' ' << y << '\n';
		}
		out.close();

		system("./fotbal2");
		system("./verificator");
		if (t % 5 == 0)
			cerr << t << '\n';
	}

	return 0;
}
