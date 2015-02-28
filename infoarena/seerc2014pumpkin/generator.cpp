#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

ofstream out("date.in");

int main() {
	int n = 60000;
	int k = 60000;
	out << n << ' ' << k << '\n';
	for (int i = 1; i <= n; ++i)
		out << rand() % k << ' ';
	out << '\n';
	for (int i = 1; i <= k; ++i) {
		int st = rand() % k + 1;
		int dr = rand() % k + 1;
		if (st > dr)
			swap(st, dr);
		out << st << ' ' << dr << '\n';
	}
	return 0;
}
