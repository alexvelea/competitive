#include <iostream>
#include <fstream>
using namespace std;
int main() {
	for (int k = 1; k <= 15; ++k)
		for (int x = 1; x <= k; ++x)
			for (int n = 1; n <= 20; ++n) {
				ofstream out("xnumere.in");
				out << k << ' ' << x << ' ' << n << '\n';
				out.close();
				system("./xnumere");
				system("./brut");

				ifstream in("xnumere.out");
				ifstream in2("xnumere2.out");

				int a, b;
				in >> a;
				in2 >> b;
				if (a != b)
					return 0;
				in.close();
				in2.close();
			}
	return 0;
}
