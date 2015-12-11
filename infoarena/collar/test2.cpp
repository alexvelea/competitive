#include <ctime>
#include <cstdlib>

#include <fstream>
using namespace std;

ofstream out("collar.in");

int main() {
	const int n = 65520;
	out << n << '\n';
	srand(time(NULL));
	for (int i = 0; i < n; ++i)
		out << rand() << '\n';
	return 0;
}
