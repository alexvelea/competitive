#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int main() {
	int a, b, rez = 0;
 	in >> a >> b;
	for (int i = 0; i <= a; ++i)
		for (int x = 0; x <= i; ++x)
			for (int y = 0; y <= x; ++y) {
				if (i * i == x * x + y * y)
					++rez;
			}
	out << rez << '\n';
	return 0;
}
