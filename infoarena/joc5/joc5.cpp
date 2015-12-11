#include <fstream>
using namespace std;

ifstream in("joc5.in");
ofstream out("joc5.out");

int main() {
	int n;
	while (in >> n) {
		if (!n)
			break;
		int x, s = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				in >> x;
				if (i == j)
					s ^= x;
			}
		out << ((s == 0) ? (2) : (1)) << '\n';
	}
	return 0;
}
