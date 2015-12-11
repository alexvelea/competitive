#include <iostream>
#include <fstream>
using namespace std;

const int inf = 1000000000;

int main() {
	ofstream out("date.in");
	out << "2000 10\n";
	for (int i = 1; i <= 2000; ++i) {
		out << rand() << ' ';
	}
	return 0;
}
