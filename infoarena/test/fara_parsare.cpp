#include <ctime>

#include <fstream>
#include <iostream>
using namespace std;

ifstream in("date.in");

int main() {
	time_t t = clock();
	int n;
	in >> n;
	long long rez = 0;
	for (int i = 1; i <= n; ++i) {
		int aux;
		in >> aux;
		rez += aux;
	}
	cerr << rez << '\n';
	cerr << 1.0 * (clock() - t) / CLOCKS_PER_SEC << '\n';
	return 0;
}
