#include <fstream>
using namespace std;

ofstream out("twosets.in");

int main() {
	out << "1\n";
	out << "i1t\n";
	for (int i = 0; i < 1000000; ++i) {
		out << "i" << rand() % 10 << "t";
	}
	return 0;
}
