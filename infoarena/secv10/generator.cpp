#include <fstream>
using namespace std;
int main() {
	ofstream out("secv10.in");
	out << "20\n";
	for (int i = 1; i <= 20; ++i) {
		for (int i = 1; i <= 100000 / 2; ++i) {
			out << "ab";
		}
		out << '\n';
		out << "a\nb\n";
	}
	return 0;
}
