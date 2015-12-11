#include <fstream>
using namespace std;
int main() {
	ofstream out("search.in");
	out << "100 200000\n";
	for (int i = 1; i <= 100; ++i) {
		for (int j = 1; j <= 5000; ++j)
			out << "a";
		out << '\n';
	}
	int sum = 0;
	for (int i = 1; i <= 200000; ++i) {
		if (sum <= 1) {
			out << "a\n";
			++sum;
			continue;
		}
		int r = rand() % 10;
		if (r < 3) {
			out << "-\n";
			--sum;
		} else {
			out << "a\n";
			++sum;
		}
	}
	out.close();
}
