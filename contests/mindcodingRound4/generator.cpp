#include <fstream>
using namespace std;
int main() {
	for (int t = 0; t < 100; ++t) {
		ofstream out("date.txt");
		for (int i = 0; i < 14 * 14; ++i) {
			out << rand() % 6;
		}
		out.close();
		system("./d");
		system("./d2");
	}
	
	return 0;
}
