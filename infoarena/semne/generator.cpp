#include <fstream>
#include <iostream>
using namespace std;
ofstream out("semne.in");
int main() {
	int sum = 0, nr = 0;
	out << "50000 0\n";
	while (1) {
		int x, ap;
		cin >> x;
		if (x == -1)
			break;
		cin >> ap;
		while (ap--)
			out << x << ' ';
	}
	while (nr < 50000) {
		out << "0 ";
		nr++;
	}
	return 0;
}
