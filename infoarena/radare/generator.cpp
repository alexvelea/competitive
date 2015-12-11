#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;
int main() {
	srand(time(NULL));
	for (int t = 0; t < 100; ++t) {
		int n = 15, el[30];

        ofstream out("radare.in");
		out << n << ' ' << 30 << '\n';
		
		el[0] = 1;
		for (int i = 2; i <= n; ++i) {
			int x = rand() % (i - 1);
			out << el[x] << ' ' << i << '\n';
			el[i - 1] = i;
		}
		for (int i = 1; i <= n; ++i)
			out << rand() % 10 << ' ';
		out.close();

		system("./brut");
		system("./radare");

		ifstream in("radare.out");
		ifstream in2("radare2.out");

		int a, b;

		in >> a;
		in2 >> b;
		if (a != b) {
			cerr << "Problema!\t" << t << '\n';
			return 0;
		} 
		if (t % 5 == 0)
			cerr << t << '\n';
		in.close();
		in2.close();
	}
	return 0;
}
