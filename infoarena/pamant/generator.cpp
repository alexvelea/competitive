#include <ctime>
#include <cstdlib>

#include <fstream>
#include <iostream>
using namespace std;

bool edge[10005][10005];

int main() {
	srand(time(NULL));
	for (int t = 0; t < 100; ++t) {
		int n = 15;
		int m = 40;
		for (int i = 1; i <= m; ++i) {
			int x = rand() % n + 1;
			int y = rand() % n + 1;
			edge[x][y] = edge[y][x] = 1;
		}
		m = 0;
 		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (edge[i][j])
					++m;

		ofstream out("pamant.in");
		out << n << ' ' << m << '\n';
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (edge[i][j]) {
					out << i << ' ' << j << '\n';
					edge[i][j] = edge[j][i] = 0;
				}
		out.close();

		system("./pamant");
		system("./brut");

		string a, b, aux;
		ifstream in("pamant.out");
		ifstream in2("pamant2.out");

		while (in >> aux)
			a += aux;
		while (in2 >> aux)
			b += aux;

		in.close();
		in2.close();

		if (a != b) {
			cerr << "Gresit\t" << t << '\n';
			return 0;
		}
		if (t % 5 == 0)
			cerr << t << '\n';
	}
	return 0;
}
