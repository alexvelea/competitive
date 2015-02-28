#include <fstream>
using namespace std;

bool viz[200][20];

ofstream out("pavare.in");

int main() {
	int n = 150, m = 15, k = n * m / 3;
	out << n << ' ' << m << ' ' << k << '\n';
	for (int i = 1; i <= k; ++i) {
		int x = rand() % n + 1, y = rand() % m + 1;
		if (viz[x][y] == true) {
			--i;
		} else {
			out << x << ' ' << y << '\n';
		}
	}
}
