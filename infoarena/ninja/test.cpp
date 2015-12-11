#include <fstream>
#include <iostream>
using namespace std;

ofstream out("ninja.in");

int main() {
	out << "100000 100000 100000\n";
	for (int i = 1; i <= 200000; ++i)
		out << "1 100000\n";
}
