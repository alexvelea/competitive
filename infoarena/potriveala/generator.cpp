#include <fstream>
using namespace std;

ofstream out("potriveala.in");

int main() {
	srand(time(NULL));
    for (int i = 0; i < 250000; ++i)
		out << char('A' + rand() % 26);
	out << '\n';
	out << "A";
	return 0;
}
