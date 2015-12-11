#include <ctime>
#include <cstdlib>
#include <cmath>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 10005;
bool edge[kMaxN][kMaxN];

int main() {
    srand(time(NULL));

	for (int t = 0; t < 1000; ++t) {
	
    	ofstream out("drumuri5.in");
		
		int n, m;

//		n = rand() % 100;
//		n += 100;
//		m = rand() % (int(sqrt(n)) + 1) + 1;
		n = 7;
		m = 9;

//		m *= n;

 		if (n > kMaxN)
			cerr << "Error!!! N is to big\n";   	
	
    	for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				edge[i][j] = false;
		for (int j = 1; j <= m; ) {
			int a = rand() % n + 1, b = rand() % n + 1;
			if (a == b)
				continue;
			if (edge[a][b])
				continue;
			edge[a][b] = 1;
			++j;
		}

		out << n << ' ' << m << '\n';
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (edge[i][j])
					out << i << ' ' << j << '\n';
		out.close();


        system("./drumuri");
		system("./vlad");

		string aux, a, b;

		ifstream in("drumuri5.out");
		ifstream in2("drumuri2.out");

		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;

		in.close();
		in2.close();

		if (a != b) {
			cerr << "Gresit la \t" << t << '\n';
			return 0;
		}

		if (t % 10 == 0)
			cerr << t << '\n';
	}
	return 0;
}
