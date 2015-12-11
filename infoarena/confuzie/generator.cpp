#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

int father[200005];

int get_deep(int nod) {
	if (nod == 1)
		return 0;
	return 1 + get_deep(father[nod]);
}

int get_father(int nod, int h) {
	if (h == 0)
		return nod;
	return get_father(father[nod], h - 1);
}

int main() {


	const int n = 1000, m = 20000;
	
	/*const int n = 200000, m = 450000;
	ofstream out("confuzie.in");                 
	out << n << ' ' << m << '\n';
	for (int i = 1; i < n; ++i)
		out << i << ' ' << i + 1 << '\n';

	int rez = 0;
	while (1 << rez < n)
		++rez;
	cerr << rez + 1 << '\n';

	out << 0 << " 2\n";
	for (int i = 1; i < m; ++i)
		out << 1 << ' ' << 1 << ' ' << n << '\n';*/
	srand(time(NULL));
	for (int t = 0; t < 10
		0; ++t) {
  		ofstream out("confuzie.in");
		out << n << ' ' << m << '\n';
		for (int i = 2; i <= n; ++i) {
			int x = rand() % (i - 1);
			x++;
			father[i] = x;
			out << x << ' ' << i << '\n';
		}
		for (int i = 1; i <= m; ++i) {
			int x = rand() % 20;
			if (x < 7) {
				out << "0 " << rand() % n + 1 << '\n';
			} else {
				int x = rand() % n + 1;
				int h = get_deep(x);
				h = rand() % (h + 1);
				out << "1 " << get_father(x, h) << ' ' << x << '\n';
			}
		}
		out.close();
		system("./confuzie2");
		system("./brut");
		
		string a, b, aux;

		ifstream in("confuzie.out");
		ifstream in2("confuzie2.out");

		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;
		if (a != b)
			cerr << "Greseala la \t" << t << '\n';
		if (t % 10 == 0)
			cerr << "###\t" << t << '\n';
	}
	return 0;
}
