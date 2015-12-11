#include <fstream>
using namespace std;

int viz[1005][10005];

int main() {
	int n = 100, m = 1000;
	ofstream out("c.in");
	out << n << ' ' << m << '\n';
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i == 1 and j == 1) {
				out << 'x';
			} else {
				out << '.';
			}
		}
		out << "\n";
	}

	out << n * m << '\n';
	for (int i = 1; i <= n * m; ++i) {
		int l = rand() % n + 1, c = rand() % m + 1;
		if (viz[l][c] == true)
			--i;
		else
			out << l << ' ' << c << '\n';
	}
	return 0;
}
