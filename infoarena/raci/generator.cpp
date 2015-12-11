#include <fstream>
using namespace std;
int main() {
	int n = 500000;

	ofstream out("raci.in");

	out << n << ' ' << 10000 << '\n';
	for (int i = 1; i <= n; ++i) {
		out << char(rand() % 7 + 'a') << char(rand() % 7 + 'a') << ' ';
	}
}
