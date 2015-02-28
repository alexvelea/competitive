#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
int main() {
	srand(time(NULL));
	int n = 10000000;
	ofstream out("date.in");
	out << n << '\n';
	for (int i = 1; i <= n; ++i)
		out << rand() % 100 << ' ';
	out.close();
	return 0;
}
