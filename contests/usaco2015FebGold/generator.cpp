#include <fstream>
using namespace std;

ofstream out("hopscotch.in");

int main() {
	int n = 750, m = 750, maxVal = 50;
	out << n << ' ' << m << ' ' << maxVal << '\n';
	for (int i = 1; i <= n; ++i, out << '\n')
		for (int j = 1; j <= m; ++j) {
			out << rand() % maxVal + 1 << ' ';
		}
	out.close();
	return 0;
}
