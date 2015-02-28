#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int edge[1005][1005], viz[1005];

int main() {
	const int N = 1000, M = 1000, X = 5;
	srand(time(NULL));
	for (int t = 0; t < 100; ++t) {
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				edge[i][j] = false;
		for (int i = 1; i <= N; ++i) {
			edge[i][i] = true;
			viz[i] = false;
		}
		int m = M;
		for (int i = 1; i <= M; ++i) {
        	int a = rand() % N + 1, b = rand() % N + 1;
			m -= edge[a][b];
			edge[a][b] = edge[b][a] = true;
		}
		int x = X;
		for (int i = 1; i <= X; ++i) {
        	int a = rand() % N + 1;
			x -= viz[a];
			viz[a] = true;
		}

		ofstream out("reinvent.in");
		out << N << ' ' << m << ' ' << x << '\n';
		for (int i = 1; i <= N; ++i)
			for (int j = i + 1; j <= N; ++j)
				if (edge[i][j])
					out << i << ' ' << j << '\n';
		for (int i = 1; i <= N; ++i)
			if (viz[i])
				out << i << ' ';
		out.close();

		system("./reinvent");
		system("./brut");

		int a, b;
		ifstream in("reinvent.out");
		ifstream in2("reinvent2.out");
		in >> a;
		in2 >> b;
		if (a != b) {
			cerr << "Greseala la " << t;
			return 0;
		}
		cerr << t << '\n';
	}
	return 0;
}
