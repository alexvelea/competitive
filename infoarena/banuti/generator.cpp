#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
int main() {
	ofstream out("banuti.in");
 	int n = 50000;
	out << n << ' ' << 4999 << ' ';
	srand(time(NULL));
	for (int i = 2; i <= n; ++i)
		out << abs(rand()) << '\n';
}
