#include <fstream>
using namespace std;

ofstream out("progr2.in");

int main() {
	out << "10\n";
	for (int i = 1; i <= 10; ++i) {
		out << "1000\n";
		for (int j = 1; j <= 1000; ++j)
			out << j << ' ';
	}
	return 0;
}
