#include <ctime>
#include <iostream>
using namespace std;
int main() {
	clock_t s = clock(), f;
	system("./test");
	f = clock();
	cerr << 1.0 * (f - s) / CLOCKS_PER_SEC << '\n';
	return 0;
}
